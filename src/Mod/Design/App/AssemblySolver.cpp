// SPDX-License-Identifier: LGPL-2.1-or-later

#include "AssemblySolver.h"

#include <Base/Matrix.h>
#include <Base/Rotation.h>

#include <OndselSolver/ASMTAssembly.h>
#include <OndselSolver/ASMTCylindricalJoint.h>
#include <OndselSolver/ASMTFixedJoint.h>
#include <OndselSolver/ASMTMarker.h>
#include <OndselSolver/ASMTPart.h>
#include <OndselSolver/ASMTPlanarJoint.h>
#include <OndselSolver/ASMTRevoluteJoint.h>
#include <OndselSolver/ASMTSphericalJoint.h>
#include <OndselSolver/ASMTTranslationalJoint.h>
#include <OndselSolver/CREATE.h>

#include <exception>
#include <map>
#include <memory>

using namespace MbD;

namespace
{
template<class T>
void setPose(const std::shared_ptr<T>& item, const Base::Placement& p)
{
    const Base::Vector3d& v = p.getPosition();
    item->setPosition3D(v.x, v.y, v.z);
    Base::Matrix4D m;
    p.getRotation().getValue(m);
    item->setRotationMatrix(m[0][0], m[0][1], m[0][2], m[1][0], m[1][1], m[1][2], m[2][0], m[2][1], m[2][2]);
}

std::shared_ptr<ASMTJoint> joint(Design::Solver::Kind kind)
{
    using Design::Solver::Kind;
    switch (kind) {
        case Kind::Revolute: return CREATE<ASMTRevoluteJoint>::With();
        case Kind::Slider: return CREATE<ASMTTranslationalJoint>::With();
        case Kind::Cylindrical: return CREATE<ASMTCylindricalJoint>::With();
        case Kind::Planar: return CREATE<ASMTPlanarJoint>::With();
        case Kind::Ball: return CREATE<ASMTSphericalJoint>::With();
        default: return CREATE<ASMTFixedJoint>::With();
    }
}
}  // namespace

namespace
{
bool solveOnce(std::vector<Design::Solver::Part>& parts, const std::vector<Design::Solver::Link>& links, std::string& error);
}

/// Eine gestreckte Kette ist für den Solver singulär (er weiß nicht, wohin sie knicken soll): dann noch einmal von
/// leicht geknickten Startlagen aus, jedes Teil um sein Gelenk gedreht. ponytail: feste Versuchsfolge ±10°, ±30°
bool Design::Solver::solve(std::vector<Part>& parts, const std::vector<Link>& links, std::string& error)
{
    std::vector<Part> attempt = parts;
    if (solveOnce(attempt, links, error)) {
        parts = attempt;
        return true;
    }
    for (const double degrees : {10.0, -10.0, 30.0, -30.0}) {
        attempt = parts;
        for (Part& p : attempt) {
            const auto hinge = std::ranges::find(links, p.name, &Link::b);
            if (p.fixed || hinge == links.end()) {
                continue;
            }
            const Base::Placement axis = p.pose * hinge->onB;
            Base::Vector3d z;
            axis.getRotation().multVec(Base::Vector3d(0, 0, 1), z);
            const Base::Placement turn = Base::Placement(axis.getPosition(), Base::Rotation(z, degrees * M_PI / 180))
                * Base::Placement(-axis.getPosition(), Base::Rotation());
            p.pose = turn * p.pose;
        }
        std::string again;
        if (solveOnce(attempt, links, again)) {
            parts = attempt;
            return true;
        }
    }
    return false;
}

namespace
{
bool solveOnce(std::vector<Design::Solver::Part>& parts, const std::vector<Design::Solver::Link>& links, std::string& error)
{
    using Design::Solver::Kind;
    using Design::Solver::Link;
    using SolverPart = Design::Solver::Part;
    try {
        auto assembly = CREATE<ASMTAssembly>::With();
        assembly->setName("MyCAD");
        auto ground = CREATE<ASMTMarker>::With();
        ground->setName("Ground");
        assembly->addMarker(ground);
        std::map<std::string, std::shared_ptr<ASMTPart>> solverParts;
        for (const SolverPart& p : parts) {
            auto part = CREATE<ASMTPart>::With();
            part->setName(p.name);
            setPose(part, p.pose);
            assembly->addPart(part);
            solverParts[p.name] = part;
            if (p.fixed) {  // Boden: an der Stelle festhalten, an der es steht
                auto here = CREATE<ASMTMarker>::With();
                here->setName("Fix" + p.name);
                setPose(here, p.pose);
                assembly->addMarker(here);
                auto own = CREATE<ASMTMarker>::With();
                own->setName("Fix");
                part->addMarker(own);
                auto fix = CREATE<ASMTFixedJoint>::With();
                fix->setName("Ground" + p.name);
                fix->setMarkerI("/MyCAD/Fix" + p.name);
                fix->setMarkerJ("/MyCAD/" + p.name + "/Fix");
                assembly->addJoint(fix);
            }
        }
        for (const Link& l : links) {
            if (!solverParts.count(l.a) || !solverParts.count(l.b)) {
                error = "A joint refers to a component outside the assembly";
                return false;
            }
            auto ma = CREATE<ASMTMarker>::With();
            ma->setName(l.name + "A");
            setPose(ma, l.onA);
            solverParts[l.a]->addMarker(ma);
            auto mb = CREATE<ASMTMarker>::With();
            mb->setName(l.name + "B");
            setPose(mb, l.onB);
            solverParts[l.b]->addMarker(mb);
            auto j = joint(l.kind);
            j->setName(l.name);
            j->setMarkerI("/MyCAD/" + l.a + "/" + l.name + "A");
            j->setMarkerJ("/MyCAD/" + l.b + "/" + l.name + "B");
            assembly->addJoint(j);
        }
        assembly->solve();
        std::map<std::string, Base::Placement> solved;
        for (SolverPart& p : parts) {
            solved[p.name] = p.pose;
        }
        for (SolverPart& p : parts) {
            if (p.fixed) {
                continue;
            }
            double x = 0, y = 0, z = 0, q0 = 1, q1 = 0, q2 = 0, q3 = 0;
            solverParts[p.name]->getPosition3D(x, y, z);
            solverParts[p.name]->getQuarternions(q0, q1, q2, q3);  // q0 ist der Skalar
            p.pose = Base::Placement(Base::Vector3d(x, y, z), Base::Rotation(q1, q2, q3, q0));
            solved[p.name] = p.pose;
        }
        // Der Solver liefert bei Widersprüchen einen Kompromiss statt eines Fehlers: jedes Gelenk nachprüfen
        for (const Link& l : links) {
            const Base::Placement a = solved[l.a] * l.onA, b = solved[l.b] * l.onB;
            const Base::Vector3d d = b.getPosition() - a.getPosition();
            Base::Vector3d xa, za, xb, zb;
            a.getRotation().multVec(Base::Vector3d(1, 0, 0), xa);
            a.getRotation().multVec(Base::Vector3d(0, 0, 1), za);
            b.getRotation().multVec(Base::Vector3d(1, 0, 0), xb);
            b.getRotation().multVec(Base::Vector3d(0, 0, 1), zb);
            const double off = (d - za * (d * za)).Length();  // Abstand quer zur Achse
            const bool axis = za * zb > 1 - 1e-8;
            bool ok = true;
            switch (l.kind) {
                case Kind::Fixed: ok = d.Length() < 1e-4 && axis && xa * xb > 1 - 1e-8; break;
                case Kind::Revolute: ok = d.Length() < 1e-4 && axis; break;
                case Kind::Ball: ok = d.Length() < 1e-4; break;
                case Kind::Slider: ok = off < 1e-4 && axis && xa * xb > 1 - 1e-8; break;
                case Kind::Cylindrical: ok = off < 1e-4 && axis; break;
                case Kind::Planar: ok = std::abs(d * za) < 1e-4 && axis; break;
            }
            if (!ok) {
                error = "The joints cannot all be met (" + l.name + ")";
                return false;
            }
        }
        return true;
    }
    catch (const std::exception& e) {
        error = std::string("The joints cannot all be met: ") + e.what();
        return false;
    }
    catch (...) {
        error = "The joints cannot all be met";
        return false;
    }
}
}  // namespace

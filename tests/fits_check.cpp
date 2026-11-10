// SPDX-License-Identifier: LGPL-2.1-or-later
// Prüfung der ISO-286-Tabelle (Idee 4), ohne FreeCAD:
//   g++ -std=c++20 -I src tests/fits_check.cpp -o /tmp/fits && /tmp/fits

#include <Mod/Design/App/Fits.h>

#include <cassert>
#include <cstdio>

using namespace Fits;

static bool is(const Deviation& d, double upper, double lower)
{
    return std::abs(d.upper - upper) < 1e-9 && std::abs(d.lower - lower) < 1e-9;
}

int main()
{
    Deviation d, hole, shaft;
    // Ø20 (Bereich 18–30)
    assert(field("H7", 20, d) && is(d, 21, 0));
    assert(field("g6", 20, d) && is(d, -7, -20));
    assert(field("h6", 20, d) && is(d, 0, -13));
    assert(field("k6", 20, d) && is(d, 15, 2));
    assert(field("p6", 20, d) && is(d, 35, 22));
    assert(field("f7", 20, d) && is(d, -20, -41));
    assert(field("H8", 20, d) && is(d, 33, 0));

    // Bereichsgrenzen: "über … bis einschließlich"
    for (double top : {3.0, 6.0, 10.0, 18.0, 30.0, 50.0, 80.0}) {
        assert(range(top) + 1 == range(top + 0.001));
    }
    assert(field("H7", 3, d) && is(d, 10, 0));
    assert(field("H7", 3.5, d) && is(d, 12, 0));
    assert(field("H7", 30, d) && is(d, 21, 0));
    assert(field("H7", 30.5, d) && is(d, 25, 0));
    assert(field("g6", 50, d) && is(d, -9, -25));
    assert(field("g6", 80, d) && is(d, -10, -29));

    // k über IT7: Grundabmaß 0
    assert(field("k8", 20, d) && is(d, 33, 0));

    // Passungen: Spiel bzw. Übermaß
    double lo, hi;
    assert(fit("H7/g6", 20, hole, shaft, lo, hi) && lo == 7 && hi == 41);
    assert(fit("H7/h6", 20, hole, shaft, lo, hi) && lo == 0 && hi == 34);
    assert(fit("H7/p6", 20, hole, shaft, lo, hi) && lo == -35 && hi == -1);
    assert(fit("H8/f7", 20, hole, shaft, lo, hi) && lo == 20 && hi == 74);
    assert(hole.mean() == 16.5 && shaft.mean() == -30.5);

    // ungültig
    assert(!field("H7", 0, d) && !field("H7", 600, d) && !field("x7", 20, d) && !field("H4", 20, d) && !field("H", 20, d));
    assert(!fit("H7", 20, hole, shaft, lo, hi));

    std::puts("fits ok");
    return 0;
}

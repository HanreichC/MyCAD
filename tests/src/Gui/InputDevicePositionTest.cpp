// SPDX-License-Identifier: LGPL-2.1-or-later
// U3 (FreeCAD#32898, PR #32899): bei gebrochener Skalierung (125 %, 150 %) lag der Pick einen Gerätepixel neben dem
// Cursor, am unteren Rand sogar außerhalb des Viewports. Erst skalieren, dann spiegeln, gegen die Höhe, mit der
// QuarterWidget den Viewport anlegt.

#include <gtest/gtest.h>

#include <QPointF>

#include <Gui/Quarter/devices/InputDevice.h>

using SIM::Coin3D::Quarter::InputDevice;

TEST(InputDevicePosition, wholeScaleFlipsTopAndBottomRow)
{
    const SbVec2s size(400, 300);
    EXPECT_EQ(InputDevice::toDevicePixelPosition(QPointF(0, 0), size, 1.0), SbVec2s(0, 299));
    EXPECT_EQ(InputDevice::toDevicePixelPosition(QPointF(399, 299), size, 1.0), SbVec2s(399, 0));
    EXPECT_EQ(InputDevice::toDevicePixelPosition(QPointF(10, 10), size, 2.0), SbVec2s(20, 579));
}

TEST(InputDevicePosition, fractionalScaleStaysInsideTheViewport)
{
    const SbVec2s size(400, 300);  // bei 150 % legt QuarterWidget 600 × 450 Gerätepixel an
    for (const double y : {0.0, 0.4, 150.2, 299.0, 299.9}) {
        const SbVec2s p = InputDevice::toDevicePixelPosition(QPointF(12.3, y), size, 1.5);
        EXPECT_GE(p[1], 0) << y;
        EXPECT_LT(p[1], 450) << y;
        EXPECT_EQ(p[1], 449 - static_cast<int>(y * 1.5)) << y;  // der Gerätepixel, der den Punkt enthält
        EXPECT_EQ(p[0], 18);
    }
}

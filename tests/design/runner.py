# SPDX-License-Identifier: LGPL-2.1-or-later
"""Startet in FreeCADCmd alle tests/design/test_*.py (Muster über $PATTERN) und beendet mit 0 oder 1."""
import os
import sys
import unittest

here = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, here)
suite = unittest.defaultTestLoader.discover(here, pattern=os.environ.get("PATTERN") or "test_*.py")
result = unittest.TextTestRunner(stream=sys.stdout, verbosity=2).run(suite)
sys.stdout.flush()
os._exit(0 if result.wasSuccessful() and result.testsRun > 0 else 1)

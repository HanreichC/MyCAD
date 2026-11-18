# SPDX-License-Identifier: LGPL-2.1-or-later
"""U1: Speichern ohne Sicherungsdateien (MyCAD-Vorgabe) ersetzt die Design-Datei in einem Schritt. Vorher löschte
FreeCAD sie zuerst und benannte die temporäre Datei erst danach um: endete MyCAD dazwischen, war das Design weg. Der
Test sieht dem Ordner per inotify zu: die Datei darf nie gelöscht werden, nur ersetzt (umbenannt auf ihren Namen)."""
import ctypes
import os
import struct
import tempfile

from design import *

IN_DELETE, IN_MOVED_TO, IN_NONBLOCK = 0x200, 0x80, 0o4000


def events(fd):
    """(Maske, Name) aller bisher gemeldeten Ereignisse"""
    out = []
    try:
        data = os.read(fd, 65536)
    except BlockingIOError:
        return out
    i = 0
    while i < len(data):
        _, mask, _, length = struct.unpack_from("iIII", data, i)
        name = data[i + 16:i + 16 + length].rstrip(b"\0").decode()
        out.append((mask, name))
        i += 16 + length
    return out


class AtomicSave(DesignTest):
    def save_twice(self, timestamp_policy):
        grp = App.ParamGet("User parameter:BaseApp/Preferences/Document")
        old = grp.GetBool("CreateBackupFiles", True), grp.GetBool("UseFCBakExtension", True)
        grp.SetBool("CreateBackupFiles", False)
        grp.SetBool("UseFCBakExtension", timestamp_policy)
        libc = ctypes.CDLL(None, use_errno=True)
        folder = tempfile.mkdtemp()
        path = os.path.join(folder, "Gehäuse.mycad")
        try:
            box(self.doc, 10, 10, 10)
            self.doc.saveAs(path)  # erstes Speichern: die Datei gibt es noch nicht
            fd = libc.inotify_init1(IN_NONBLOCK)
            self.assertGreaterEqual(fd, 0)
            libc.inotify_add_watch(fd, folder.encode(), IN_DELETE | IN_MOVED_TO)
            box(self.doc, 5, 5, 5)
            self.doc.save()  # zweites Speichern: ersetzt die vorhandene Datei
            seen = events(fd)
            os.close(fd)
        finally:
            grp.SetBool("CreateBackupFiles", old[0])
            grp.SetBool("UseFCBakExtension", old[1])
        name = os.path.basename(path)
        self.assertNotIn((IN_DELETE, name), seen, "the design file was deleted before the new one was in place")
        self.assertIn((IN_MOVED_TO, name), seen)
        self.assertEqual(sorted(os.listdir(folder)), [name])  # keine Reste, keine Sicherung

    def test_timestamp_policy(self):  # MyCAD-Vorgabe (UseFCBakExtension an)
        self.save_twice(True)

    def test_standard_policy(self):
        self.save_twice(False)

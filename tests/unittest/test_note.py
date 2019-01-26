import unittest

import marshitronica as mt


class TestNote(unittest.TestCase):

    def setUp(self):
        super(TestNote, self).setUp()
        self.note = mt.Note(60, 1, 0.5)

    def test_get_pitch(self):
        self.assertEqual(60, self.note.get_pitch())

    def test_get_duration(self):
        self.assertEqual(1, self.note.get_duration())

    def test_get_amp(self):
        self.assertEqual(0.5, self.note.get_amp())

import unittest

import marshitronica as mt


class TestPhrase(unittest.TestCase):

    def setUp(self):
        super(TestPhrase, self).setUp()

    def test_get_length(self):
        phrase = mt.NotesPhrase()
        self.assertEqual(0, phrase.get_length())
        phrase.add_note(0, mt.Note(60, 1, 0.5))
        self.assertEqual(1, phrase.get_length())

    def test_get_events_in_range(self):
        phrase = mt.NotesPhrase()
        for i in [0, 0.2, 0.5, 1, 2]:
            phrase.add_note(i, mt.Note(60, 1, 0.5))
        events = phrase.get_events_in_range(0, 1)
        self.assertEqual(3, len(events))
        self.assertEqual(0, events[0][0])
        self.assertEqual(0.2, events[1][0])
        self.assertEqual(0.5, events[2][0])

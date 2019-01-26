import unittest

import marshitronica as mt


class TestPhrase(unittest.TestCase):

    def setUp(self):
        super(TestPhrase, self).setUp()

    def test_get_length(self):
        phrase = mt.Phrase()
        self.assertEqual(0, phrase.get_length())
        phrase.add_note(0, mt.Note(60, 1, 0.5))
        self.assertEqual(1, phrase.get_length())

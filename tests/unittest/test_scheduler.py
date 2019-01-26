import unittest

import marshitronica as mt


class TestScheduler(unittest.TestCase):

    def setUp(self):
        super(TestScheduler, self).setUp()
        self.scheduler = mt.Scheduler()

    def test_seconds_to_beats(self):
        self.assertEqual(2, self.scheduler.seconds_to_beats(1))

    def test_beats_to_seconds(self):
        self.assertEqual(0.5, self.scheduler.beats_to_seconds(1))

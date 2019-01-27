import unittest
import time

import marshitronica as mt


class Incrementer(object):
    def __init__(self):
        self.x = 0

    def __call__(self):
        self.x += 1


class TestScheduler(unittest.TestCase):

    def setUp(self):
        super(TestScheduler, self).setUp()

    def test_seconds_to_beats(self):
        scheduler = mt.Scheduler()
        self.assertEqual(2, scheduler.seconds_to_beats(1))

    def test_beats_to_seconds(self):
        scheduler = mt.Scheduler()
        self.assertEqual(0.5, scheduler.beats_to_seconds(1))

    def test_scheduling(self):
        scheduler = mt.Scheduler()
        scheduler.start()
        incrementer = Incrementer()
        scheduler.add_task(1, incrementer)
        time.sleep(0.4)
        self.assertEqual(0, incrementer.x)
        time.sleep(0.2)
        self.assertEqual(1, incrementer.x)

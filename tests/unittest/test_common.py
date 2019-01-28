import unittest

import marshitronica as mt


class TestCommon(unittest.TestCase):

    def setUp(self):
        super(TestCommon, self).setUp()
        self.common1 = mt.Common.get()
        self.common2 = mt.Common.get()

    def test_next_bus_id(self):
        next_bus_id1 = self.common1.get_next_bus_id()
        next_bus_id2 = self.common2.get_next_bus_id()
        self.assertEqual(next_bus_id1, next_bus_id2)
        self.common1.increment_next_bus_id()
        self.assertEqual(self.common1.get_next_bus_id(), next_bus_id1 + 2)
        self.assertEqual(self.common2.get_next_bus_id(), next_bus_id1 + 2)

    def test_next_synth_id(self):
        next_synth_id1 = self.common1.get_next_synth_id()
        next_synth_id2 = self.common2.get_next_synth_id()
        self.assertEqual(next_synth_id1, next_synth_id2)
        self.common1.increment_next_synth_id()
        self.assertEqual(self.common1.get_next_synth_id(), next_synth_id1 + 1)
        self.assertEqual(self.common2.get_next_synth_id(), next_synth_id1 + 1)

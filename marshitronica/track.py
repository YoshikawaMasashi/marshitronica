import numpy as np
from pythonosc import osc_message_builder

import marshitronica


class Track(object):
    def __init__(self):
        self.phrase = None
        self.length = None
        self.scheduler = None

        self.bus_id = marshitronica.NEXT_BUS_ID
        marshitronica.NEXT_BUS_ID += 2

        msg = osc_message_builder.OscMessageBuilder(address='/s_new')
        msg.add_arg("output", arg_type='s')
        msg.add_arg(marshitronica.NEXT_SYNTH_ID, arg_type='i')
        msg.add_arg(0, arg_type='i')
        msg.add_arg(0, arg_type='i')
        msg.add_arg("in", arg_type='s')
        msg.add_arg(self.bus_id, arg_type='i')
        msg = msg.build()
        marshitronica.client.send(msg)

        marshitronica.NEXT_SYNTH_ID += 1

    def set_phrase(self, phrase):
        self.phrase = phrase
        self.length = self.phrase.length

    def set_scheduler(self, scheduler):
        self.scheduler = scheduler

    @property
    def now_repeats(self):
        return self.scheduler.now_beats // self.length

    @property
    def now_beats(self):
        return self.scheduler.now_beats % self.length

    @property
    def next_beats(self):
        beats_list = np.array(self.phrase.beats_list)
        tmp = beats_list > self.now_beats
        if tmp.sum() > 0:
            return beats_list[tmp].min()
        else:
            return beats_list.min()

    @property
    def next_scheduler_beats(self):
        beats_list = np.array(self.phrase.beats_list)
        tmp = beats_list > self.now_beats
        if tmp.sum() > 0:
            return beats_list[tmp].min() + self.length * self.now_repeats
        else:
            return beats_list.min() + self.length * (self.now_repeats + 1)

    def next_beats_of_beats(self, beats):
        beats_list = np.array(self.phrase.beats_list)
        tmp = beats_list > beats
        if tmp.sum() > 0:
            return beats_list[tmp].min()
        else:
            return beats_list.min()

    def next_scheduler_beats_of_beats(self, beats):
        beats_list = np.array(self.phrase.beats_list)
        tmp = beats_list > beats
        if tmp.sum() > 0:
            return beats_list[tmp].min() + self.length * self.now_repeats
        else:
            return beats_list.min() + self.length * (self.now_repeats + 1)

    def play(self):
        self.recursive_schedule(self.next_scheduler_beats)

    def recursive_schedule(self, scheduler_beats):
        def f():
            beats = scheduler_beats % self.length
            self.recursive_schedule(
                self.next_scheduler_beats_of_beats(beats))
            self.send_osc(beats)

        self.scheduler.add_callable(scheduler_beats, f)

    def pitch_to_freq(self, pitch):
        return 440 * 2 ** ((pitch - 69) / 12)

    def send_osc(self, beats):
        notes = self.phrase.notes[beats]
        for note in notes:
            msg = osc_message_builder.OscMessageBuilder(address='/s_new')
            msg.add_arg("smooth", arg_type='s')
            msg.add_arg(marshitronica.NEXT_SYNTH_ID, arg_type='i')
            msg.add_arg(0, arg_type='i')
            msg.add_arg(0, arg_type='i')
            msg.add_arg("out", arg_type='s')
            msg.add_arg(self.bus_id, arg_type='i')
            msg.add_arg("amp", arg_type='s')
            msg.add_arg(note.amp, arg_type='f')
            msg.add_arg("sustain", arg_type='s')
            msg.add_arg(
                self.scheduler.beats_to_time(note.duration), arg_type='f')
            msg.add_arg("freq", arg_type='s')
            msg.add_arg(self.pitch_to_freq(note.pitch), arg_type='f')
            msg = msg.build()
            marshitronica.client.send(msg)

            marshitronica.NEXT_SYNTH_ID += 1

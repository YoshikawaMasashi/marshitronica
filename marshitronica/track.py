import numpy as np


class Track(object):
    def __init__(self):
        self.phrase = None
        self.length = None
        self.scheduler = None

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

    def send_osc(self, beats):
        notes = self.phrase.notes[beats]
        for note in notes:
            print(note.pitch)

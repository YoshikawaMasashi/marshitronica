import collections


class Note(object):
    def __init__(self, pitch, duration, amp):
        self.pitch = pitch
        self.duration = duration
        self.amp = amp


class Phrase(object):
    def __init__(self):
        self.notes = collections.OrderedDict()
        self.length = 0

    def add_note(self, beats, note):
        if beats not in self.notes:
            self.notes[beats] = [note]
        else:
            self.notes[beats].append(note)
        self.length = max([self.length, beats + note.duration])

    @property
    def beats_list(self):
        return list(self.notes.keys())

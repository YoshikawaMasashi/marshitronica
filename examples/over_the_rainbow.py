import time

import marshitronica as mt


phrase = mt.NotesPhrase()
track = mt.Track()

pitch = [60, 72, 71, 67, 69, 71, 72, 60, 69, 67,
         60, 65, 64, 60, 62, 64, 65, 62, 59, 60, 62, 64, 60]
dur = [2, 2, 1, 0.5, 0.5, 1, 1, 2, 2, 4,
       2, 2, 1, 0.5, 0.5, 1, 1, 1, 0.5, 0.5, 1, 1, 4]
beats = [0, 2, 4, 5, 5.5, 6, 7, 8, 10, 12,
         16, 18, 20, 21, 21.5, 22, 23, 24, 25, 25.5, 26, 27, 28]

for p, d, b in zip(pitch, dur, beats):
    note = mt.Note(p, d, 1.0)
    phrase.add_note(b, note)

track.set_phrase(phrase)

track.play()

time.sleep(20)

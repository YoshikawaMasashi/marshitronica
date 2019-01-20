
s.quit();
s.boot();

s.dumpOSC();

(
SynthDef("smooth",
	{
		arg out = 0, freq = 440, sustain = 1, amp = 0.5;
		var sig;
		sig = SinOsc.ar(freq, 0, amp) * EnvGen.kr(Env.linen(0.05, sustain, 0.1), doneAction: Done.freeSelf);
		Out.ar(out, sig ! 2);
	}
).add;

SynthDef.new("pitchShift",
	{
		arg in=0, out=0, shift=0;
		var sig;
		sig = In.ar(in, 2);
		sig = PitchShift.ar(sig, 0.05, 2 ** (shift / 12), 0, 0);
		Out.ar(out, sig);
	}
).add;

SynthDef.new("output",
	{
		arg in=0;
		var sig;
		sig = In.ar(in, 2);
		Out.ar(0, sig);
	}
).add;
)

(
var midi, dur, index;
midi = Pseq([60, 72, 71, 67, 69, 71, 72, 60, 69, 67], 1).asStream;
dur = Pseq([2, 2, 1, 0.5, 0.5, 1, 1, 2, 2, 3], 1).asStream;
index = 0;

s.sendMsg(\s_new, \output, 10000, 0, 0, \in, 7);

s.sendMsg(\s_new, \pitchShift, 10001, 0, 0, \in, 5, \out, 7, \shift, -3);

r = Task({
    var delta;
    while {
        delta = dur.next;
        delta.notNil
    } {
		s.sendMsg(\s_new, \smooth, 10002 + index, 0, 0, \amp, 0.75, \sustain, delta, \out, 5, \freq, midi.next.midicps);
		index = index + 1;
        delta.yield;
    }
}).play(quant: TempoClock.default.beats + 1.0);
)

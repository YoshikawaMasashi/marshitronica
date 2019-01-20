(
SynthDef.new(\startSound,
{ arg bus, rate=1, sus; var osc;
	ReplaceOut.kr(bus, rate)}).add;

SynthDef.new(\saw,
{|amp=1, sus=1, pan=0, freq=0, vib=0, fmod=0, rate=0, bus=0|
var osc, env;
freq = In.kr(bus, 1);
freq = [freq, freq+fmod];
amp=(amp / 8);
osc=Saw.ar(freq);
osc=(osc * amp);
env=EnvGen.ar(Env(times: [0.01, (sus - 0.01), 0.01],levels: [0, 1, 1, 0],curve: 'lin'), doneAction: 0);
osc=(osc * env);
osc = Mix(osc) * 0.5;
osc = Pan2.ar(osc, pan);
	ReplaceOut.ar(bus, osc)}).add;

SynthDef.new(\makeSound,
{ arg bus, sus; var osc;
	osc = In.ar(bus, 2);
  osc = EnvGen.ar(Env([1,1,0],[sus * 8, 0.1]), doneAction: 14) * osc;
	DetectSilence.ar(osc, amp:0.0001, time: 0.1, doneAction: 14);
Out.ar(0, osc[0]);
Out.ar(1, osc[1]);
 }).add;
)


~g = Group.head(s);

(
Synth.tail(~g, "saw", ["amp", 0.75, "sus", 1, "bus", 152, "freq", 523.251, "fmod", 0.5, "pan", 1, "rate", 1]);
Synth.tail(~g, "makeSound", ["bus", 152, "sus", 1]);
)

(
SynthDef.new(\saw,
{|amp=1, sus=1, pan=0, freq=0, vib=0, fmod=0, rate=0, bus=0|
var osc, env;
freq = In.kr(bus, 1);
freq = [freq, freq+fmod];
amp=(amp / 8);
osc=Saw.ar(freq);
osc=(osc * amp);
env=EnvGen.ar(Env(times: [0.01, (sus - 0.01), 0.01],levels: [0, 1, 1, 0],curve: 'lin'), doneAction: 0);
osc=(osc * env);
osc = Mix(osc) * 0.5;
osc = Pan2.ar(osc, pan);
	Out.ar(0, osc)}).add;

SynthDef.new(\piano,
{|amp=1, sus=1, pan=0, freq=0, vib=0, fmod=0, rate=0, bus=0|
var osc, env;
freq = In.kr(bus, 1);
freq = [freq, freq+fmod];
amp=(amp * 0.7);
osc=MdaPiano.ar((freq[0]), vel: (40 + (amp * 60)), decay: (sus / 4));
env=EnvGen.ar(Env(times: [sus],levels: [(amp * 1), (amp * 1)],curve: 'step'), doneAction: 0);
osc=(osc * env);
osc = Mix(osc) * 0.5;
osc = Pan2.ar(osc, pan);
	Out.ar(0, osc)}).add;
)



~g = Group.head(s);

(
Synth.tail(~g, "saw", ["amp", 0.75, "sus", 1, "bus", 152, "freq", 523.251, "fmod", 0.5, "pan", 1, "rate", 1]);
)

SynthDef.new("saw",
	{
		arg amp=1, sus=1, freq=0, bus=0;
		var osc, env;
		osc=Saw.ar(freq) * amp;
		osc= osc * EnvGen.ar(Env(times: [0.01, (sus - 0.01), 0.01],levels: [0, 1, 1, 0],curve: 'lin'), doneAction: 0);
		Out.ar(bus, [osc, osc]);
	}
).add;

SynthDef.new("output",
	{
		arg bus=0;
		var osc;
		osc = In.ar(bus, 2);
		Out.ar(0, osc[0]);
		Out.ar(1, osc[1]);
	}
).add;

Synth("output", [bus: 4]);
Synth("saw", [amp: 0.75, sus: 1, bus: 4, freq: 523.251]);

~g = Group.head(s);
(
Synth.tail(~g, "saw", ["amp", 0.75, "sus", 1, "bus", 4, "freq", 523.251]);
Synth.tail(~g, "output", ["bus", 4]);
)


(
var midi, dur;
midi = Pseq([60, 72, 71, 67, 69, 71, 72, 60, 69, 67], 1).asStream;
dur = Pseq([2, 2, 1, 0.5, 0.5, 1, 1, 2, 2, 3], 1).asStream;


SynthDef("smooth",
	{
		arg bus = 0, freq = 440, sustain = 1, amp = 0.5;
		var sig;
		sig = SinOsc.ar(freq, 0, amp) * EnvGen.kr(Env.linen(0.05, sustain, 0.1), doneAction: Done.freeSelf);
		Out.ar(bus, sig ! 2);
	}
).add;

SynthDef.new("output",
	{
		arg bus = 0;
		var osc;
		osc = In.ar(bus, 2);
		Out.ar(0, osc[0]);
		Out.ar(1, osc[1]);
	}
).add;

Synth("output", [bus: 5]);

r = Task({
    var delta;
    while {
        delta = dur.next;
        delta.notNil
    } {
		Synth("smooth", [freq: midi.next.midicps, sustain: delta]);
        delta.yield;
    }
}).play(quant: TempoClock.default.beats + 1.0);
)

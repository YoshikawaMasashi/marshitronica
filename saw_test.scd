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

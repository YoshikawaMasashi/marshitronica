SynthDef("smooth",
	{
		arg bus = 0, freq = 440, sustain = 1, amp = 0.5;
		var sig;
		sig = SinOsc.ar(freq, 0, amp) * EnvGen.kr(Env.linen(0.05, sustain, 0.1), doneAction: Done.freeSelf);
		Out.ar(bus, sig ! 2);
	}
).add;

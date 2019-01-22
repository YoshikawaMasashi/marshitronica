SynthDef.new("pitchShift",
	{
		arg in=0, out=0;
		var sig;
		sig = In.ar(in, 2);
		sig = PitchShift.ar(sig, 0.2, 0.5, 0, 0.0001);
		Out.ar(out, sig);
	}
).store();

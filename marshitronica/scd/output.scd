SynthDef.new("output",
	{
		arg in=0;
		var osc;
		osc = In.ar(in, 2);
		Out.ar(0, osc);
	}
).add;

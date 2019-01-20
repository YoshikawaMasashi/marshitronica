SynthDef.new("output",
	{
		arg bus = 0;
		var osc;
		osc = In.ar(bus, 2);
		Out.ar(0, osc[0]);
		Out.ar(1, osc[1]);
	}
).add;

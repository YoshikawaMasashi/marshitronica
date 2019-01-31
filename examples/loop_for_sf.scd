// Create buffer and SynthDef
(
// read a whole sound into memory
b = Buffer.read(s,Platform.resourceDir +/+ "sounds/a11wlk01.wav");

// make a simple sampler instrument
SynthDef("help-LoopBuf",{
    arg out=0, bufnum=0, rate=1, glide=0, gate=1, loopRel=0, startPos=0, startLoop, endLoop, ipol=2;
    var env, signal;
	gate = (Line.kr(0,1,10) < 1) * 300;
    rate = Lag.kr(rate, glide);
    env = EnvGen.ar(Env.adsr(0.1,0.2,1,2), gate, doneAction: 2);
    signal = LoopBuf.ar(1,bufnum, BufRateScale.kr(bufnum) * rate, gate+loopRel, startPos, startLoop, endLoop, ipol);
    Out.ar(out, (signal * env).dup);
}).send(s);
)

s.sendMsg("/s_new", "help-LoopBuf", 3000, 1, 0, \bufnum, b.bufnum, \startLoop, 150000, \endLoop, 188893);

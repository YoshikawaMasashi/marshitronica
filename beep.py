import tempfile

from pythonosc import osc_message_builder
from pythonosc import udp_client

# To use this code, you need to run `s.boos();` in SuperCollider.


client = udp_client.SimpleUDPClient('localhost', 57110)

test_orc_synth_def = """
SynthDef("test_osc", {
    var out;
    out = SinOsc.ar([220, 221],0,0.5);
    Out.ar(0, out);
}).store;
"""

fp = tempfile.NamedTemporaryFile()
fp.write(test_orc_synth_def.encode())
fp.seek(0)
print(fp.read())
fp.close()


msg = osc_message_builder.OscMessageBuilder(address='/d_load')
msg.add_arg(fp.name, arg_type='s')
msg = msg.build()
client.send(msg)

msg = osc_message_builder.OscMessageBuilder(address='/s_new')
msg.add_arg("test_osc", arg_type='s')
msg.add_arg(1000, arg_type='i')
msg.add_arg(1, arg_type='i')
msg.add_arg(1, arg_type='i')
msg = msg.build()
client.send(msg)

msg = osc_message_builder.OscMessageBuilder(address='/n_free')
msg.add_arg(1000, arg_type='i')
msg = msg.build()
client.send(msg)

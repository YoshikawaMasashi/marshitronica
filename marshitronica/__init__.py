import glob
import os
import pathlib

from pythonosc import osc_message_builder
from pythonosc import udp_client

from marshitronica.scheduler import Scheduler  # NOQA
from marshitronica.phrase import Phrase  # NOQA
from marshitronica.track import Track  # NOQA
from marshitronica.phrase import Note  # NOQA


# load synthdef
module_path = pathlib.Path(os.path.dirname(__file__))

client = udp_client.SimpleUDPClient('localhost', 57110)

for path in glob.glob(str(module_path / 'scd/*.scd')):
    msg = osc_message_builder.OscMessageBuilder(address='/d_load')
    msg.add_arg(path, arg_type='s')
    msg = msg.build()
    client.send(msg)

NEXT_BUS_ID = 4
NEXT_SYNTH_ID = 10000

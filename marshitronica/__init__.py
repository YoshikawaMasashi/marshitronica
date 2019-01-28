import glob
import os
import pathlib

from pythonosc import osc_message_builder
from pythonosc import udp_client

from marshitronica.cpplib import Scheduler  # NOQA
from marshitronica.cpplib import NotesPhrase  # NOQA
from marshitronica.cpplib import Track  # NOQA
from marshitronica.cpplib import Note  # NOQA
from marshitronica.cpplib import Common  # NOQA

# load synthdef
module_path = pathlib.Path(os.path.dirname(__file__))

client = udp_client.SimpleUDPClient('localhost', 57110)

for path in glob.glob(str(module_path / 'scsyndef/*.scsyndef')):
    msg = osc_message_builder.OscMessageBuilder(address='/d_load')
    msg.add_arg(path, arg_type='s')
    msg = msg.build()
    client.send(msg)

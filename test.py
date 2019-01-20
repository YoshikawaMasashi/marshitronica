import marshitronica as mt
import time

sch = mt.Scheduler()
sch.start()

sch.add_callable(1, lambda: print("Debug"))

time.sleep(2)

sch.stop()

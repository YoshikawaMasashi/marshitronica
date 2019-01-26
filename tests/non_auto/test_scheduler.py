import marshitronica as mt
import time


sch = mt.cpplib.Scheduler()


def print_func(i):
    def f():
        print(i)
    return f


fs = []
for i in range(4):
    f = print_func(i)
    fs.append(f)
    sch.add_task(i, f)

sch.start()
time.sleep(3)
sch.stop()
time.sleep(0.1)

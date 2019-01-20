import time
import threading
import collections


class Scheduler(object):
    """Scheduler
    """
    def __init__(self):
        self.is_running = False
        self.start_time = None
        self.step_second = 0.0001
        self.queue = collections.OrderedDict()
        self.th = None

    def __run(self):
        while self.is_running:
            if len(self.queue):
                next = list(self.queue.keys())[0]
                if next < time.time() - self.start_time:
                    callables = self.queue.pop(next)
                    for collable in callables:
                        collable()
                    continue
            time.sleep(self.step_second)

    def start(self):
        """Start
        """
        # TODO: if started, raise Exception
        self.is_running = True
        self.start_time = time.time()
        self.th = threading.Thread(target=self.__run)
        self.th.start()

    def stop(self):
        """Stop
        """
        self.is_running = False
        self.start_time = None

    def add_callable(self, time, callable):
        if time not in self.queue:
            self.queue[time] = [callable]
        else:
            self.queue.append(callable)

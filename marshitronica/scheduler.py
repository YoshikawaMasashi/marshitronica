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
        self.bpm = 120

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

    def time_to_beats(self, time):
        return time * self.bpm / 60

    def beats_to_time(self, beats):
        return beats * 60 / self.bpm

    @property
    def now(self):
        return time.time() - self.start_time

    @property
    def now_beats(self):
        return self.time_to_beats(self.now)

    def add_callable(self, beats, callable):
        t = self.beats_to_time(beats)

        if t < time.time() - self.start_time:
            return

        if t not in self.queue:
            self.queue[t] = [callable]
        else:
            self.queue.append(callable)

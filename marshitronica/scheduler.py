import time
import threading

# TODO: ASAP, use sched module


class Scheduler(object):
    """Scheduler
    """
    def __init__(self):
        self.is_running = False
        self.start_time = None
        self.step_second = 0.0001

    def __run(self):
        while self.is_running:
            time.sleep(self.step_second)

    def start(self):
        """Start
        """
        # TODO: if started, raise Exception
        self.is_running = True
        self.start_time = time.time()
        threading.Thread(None, self.__run)

    def stop(self):
        """Stop
        """
        self.is_running = False
        self.start_time = None

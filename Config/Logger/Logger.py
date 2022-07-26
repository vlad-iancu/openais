class Logger:
    def __init__(self, loggerName) -> None:
        self.name = loggerName

DEBUG: int = 0
NOTICE: int = 1
INFO: int = 2
WARN: int = 3
ERROR: int = 4
FATAL: int = 5

from Logger.Logger import Logger

class ConsoleLogger(Logger):
    def __init__(self) -> None:
        super().__init__("ConsoleLogger")

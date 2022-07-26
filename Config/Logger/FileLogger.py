from Logger.Logger import *
import os
homeVar = os.getenv("HOME")
homeDir: str = homeVar if homeVar else "/home/openais"
logDir = os.path.join(homeDir, 'logs')
class FileLogger(Logger):
    def __init__(self) -> None:
        super().__init__("FileLogger")
        self.directory = logDir
        self.filePrefix = "LOG"
        self.fileSize = 1024 * 5 #5KB by default

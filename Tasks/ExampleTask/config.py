from Logger.ConsoleLogger import ConsoleLogger
from Logger.Logger import *

Interfaces = {}
frequencyHz = 1.0
TMP = {
    "address": "127.0.0.1",
    "port": 7892,
    "threads": 4
}
printStr = "Config parameter"
consoleLogger = ConsoleLogger()
logLevel = DEBUG
loggers = [consoleLogger]

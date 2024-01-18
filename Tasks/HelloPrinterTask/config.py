from Logger.ConsoleLogger import ConsoleLogger
from Logger.Logger import *

Interfaces = {
    "PersonOutput": "PersonPrinter",
}
frequencyHz = 1.0

consoleLogger = ConsoleLogger()
logLevel = DEBUG
loggers = [consoleLogger]

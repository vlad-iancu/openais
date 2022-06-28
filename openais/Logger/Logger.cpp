#include <Logger/LogLevel.h>
#include <Logger/LogEntry.hpp>
#include <Logger/Logger.hpp>
#include <utility>
#include <iostream>

using namespace openais::logger;

Logger *Logger::g_loggers[MAX_LOGGERS];
int Logger::g_nrLoggers = 0;
std::map<std::string, Logger*> Logger::g_loggersMap;
LogLevel Logger::g_logLevel;

void Logger::AddLogger(Logger *logger)
{
	g_loggers[g_nrLoggers] = logger;
	g_nrLoggers++;
}

void Logger::LogEntry(LogEntryPtr entry)
{
	if(g_logLevel > entry->GetLevel())
	{
		return;
	}
	for(auto &[loggerName, logger] : g_loggersMap)
	{
		logger->Log(entry);
	}
}

void Logger::Configure(const Config &config)
{
	std::map<std::string, Logger*> loggers;
	for(int i = 0; i < g_nrLoggers; ++i)
	{
		std::pair<std::string, Logger*> entry = std::make_pair(g_loggers[i]->GetName(), g_loggers[i]);
		loggers.insert(entry);
	}
	for(const Config &loggerElement : config["loggers"])
	{
		Logger *logger = loggers.at(loggerElement["name"].Get<std::string>());
		g_loggersMap.insert(std::make_pair(logger->GetName(), logger));
		logger->Initialize(loggerElement);
	}
	g_logLevel = (LogLevel)(config["logLevel"].Get<int>());
}

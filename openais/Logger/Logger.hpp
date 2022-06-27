#ifndef OPENAIS_LOGGER_LOGGER_H
#define OPENAIS_LOGGER_LOGGER_H

#include "Logger/LogLevel.h"
#include <Logger/LogEntry.hpp>
#include <Task/Config.hpp>

#include <map>
#include <memory>
#include <string>

using openais::task::Config;

namespace openais {
	namespace logger {
		
		class Logger
		{
		private:
			static Logger *g_loggers[MAX_LOGGERS];
			static int g_nrLoggers;
			static std::map<std::string, Logger*> g_loggersMap;
			static LogLevel g_logLevel;

		public:
			virtual	void Log(LogEntryPtr entry) = 0;
			virtual void Initialize(const Config &config) = 0;
			virtual std::string GetName() const = 0;

		public:
			static void AddLogger(Logger *logger);
			static void LogEntry(LogEntryPtr entry);
			static void Configure(const Config &config);
		};
	}
} // namespace openais

#endif

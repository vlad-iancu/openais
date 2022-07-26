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
			/**
			 * @brief Logs a log entry
			 */
			virtual	void Log(LogEntryPtr entry) = 0;
			/**
			 * @brief Initializes the logger
			 */
			virtual void Initialize(const Config &config) = 0;
			/**
			 * @brief Gets the name of the logger
			 */
			virtual std::string GetName() const = 0;
			virtual void Clean() = 0;

		public:
			static void AddLogger(Logger *logger);
			static void LogEntry(LogEntryPtr entry);
			static void Configure(const Config &config);
			static void Release();
		};
	}
} // namespace openais

#endif

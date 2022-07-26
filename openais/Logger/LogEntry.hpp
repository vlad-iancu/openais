#ifndef OPENAIS_LOGGER_LOGENTRY_H
#define OPENAIS_LOGGER_LOGENTRY_H

#include <chrono>
#include <Time/Time.hpp>
#include <Logger/LogLevel.h>
#include <memory>
#include <string>

#ifndef MAX_LOGGERS
#define MAX_LOGGERS 1000
#endif

namespace openais 
{
	namespace logger 
	{
		using openais::time::TimeStamp;
		class LogEntry
		{
		public:
			LogEntry(
						LogLevel level,
						std::string domain,
						const std::string &message,
						TimeStamp timeStamp
					);

		public:
			/**
			 * @brief Gets the Unix timestamp (nanoseconds) when this log entry was created
			 */
			TimeStamp GetTimeStamp() const;

			/**
			 * @brief Gets the text message provided by the user
			 */
			const std::string& GetMessage() const;

			/**
			 * @brief Gets the level of this log entry.
			 * See `enum LogLevel` for possible values
			 */
			LogLevel GetLevel() const;

			/**
			 * @brief Gets the domain of this log entry
			 */
			const std::string& GetDomain() const;
				
		private:
			TimeStamp m_timeStamp;
			std::string m_message;
			LogLevel m_level;
			std::string m_domain;
		};
		using LogEntryPtr = std::shared_ptr<LogEntry>;

		std::string LogLevelToString(LogEntryPtr entry);
	}
}

#endif

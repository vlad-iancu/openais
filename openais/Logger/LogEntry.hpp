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
			TimeStamp GetTimeStamp() const;
			const std::string& GetMessage() const;
			LogLevel GetLevel() const;
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

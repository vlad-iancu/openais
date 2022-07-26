#include <Logger/LogEntry.hpp>
#include <stdexcept>

using namespace openais::logger;

TimeStamp LogEntry::GetTimeStamp() const
{
	return m_timeStamp;	
}

const std::string& LogEntry::GetMessage() const
{
	return m_message;
}

LogLevel LogEntry::GetLevel() const
{
	return m_level;
}

const std::string& LogEntry::GetDomain() const
{
	return m_domain;
}

LogEntry::LogEntry(
					LogLevel level,
					std::string domain,
					const std::string &message,
					TimeStamp timeStamp
				  )
	:
		m_level(level),
		m_domain(domain),
		m_message(message),
		m_timeStamp(timeStamp)
{

}
namespace openais 
{
	namespace logger
	{

		std::string LogLevelToString(LogEntryPtr entry)
		{
			switch (entry->GetLevel()) 
			{
				case DEBUG:
				{
					return "DEBUG";
				}
				break;
				case NOTICE:
				{
					return "NOTICE";
				}
				break;
				case INFO:
				{
					return "INFO";
				}
				break;
				case WARN:
				{
					return "WARN";
				}
				break;
				case ERROR:
				{
					return "ERROR";
				}
				break;
				case FATAL:
				{
					return "FATAL";
				}
				default:
				{
					throw std::invalid_argument("invalid log level");
				}
				break;
			}
		}
	}
}

#include <Logger/Logger.hpp>
#include <ConsoleLogger.hpp>
#include <iostream>
#include <ctime>
#include <string>

using namespace openais::logger;

ConsoleLogger ConsoleLogger::_prototype;

void ConsoleLogger::Log(LogEntryPtr entry)
{
	time_t t = (time_t)entry->GetTimeStamp();
	struct tm* utcTime;
	std::time(&t);
	utcTime = std::gmtime(&t);
	std::cout << "(" << entry->GetTimeStamp() << ") "
		      << utcTime->tm_year + 1900 << "-" << utcTime->tm_mon + 1 << "-" << utcTime->tm_mday << " "
		      << utcTime->tm_hour << ":" << utcTime->tm_min << ":" << utcTime->tm_sec << " "
			  << LogLevelToString(entry) << " [" << entry->GetDomain() << "] "
			  << entry->GetMessage() << std::endl;
}

std::string ConsoleLogger::GetName() const
{
	return "ConsoleLogger";
}

void ConsoleLogger::Initialize(const task::Config &config)
{
	/*Empty*/
}

void ConsoleLogger::Clean()
{
	/*Empty*/
}

ConsoleLogger::ConsoleLogger(const ConsoleLogger &other)
{
	/*Empty*/
}

ConsoleLogger::ConsoleLogger()
{
	Logger::AddLogger(this);
}

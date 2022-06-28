#include <Logger/LogEntry.hpp>
#include <Logger/Log.h>
#include <Logger/Logger.hpp>
#include <Time/Time.hpp>
#include <cstdarg>
#include <cstdio>
#include <memory>
#include <vector>

void log_entry(int level, const char *domain, ...)
{
	using openais::logger::LogEntry;
	using openais::logger::LogEntryPtr;
	using openais::logger::LogLevel;
	using openais::time::Time;
	va_list v;
	va_start(v, domain);
	const char *fmt = va_arg(v, const char*);
	va_list vp;
	va_copy(vp, v);
	std::vector<char> buf(std::vsnprintf(NULL, 0,  fmt, v) + 1);
	va_end(v);
	std::vsnprintf(buf.data(), buf.size(), fmt, vp);
	va_end(vp);
	LogEntryPtr entry = std::make_shared<LogEntry>(
			(LogLevel)level,
			domain,
			buf.data(),
			Time::GetPresentTime());
	openais::logger::Logger::LogEntry(entry);
}


#ifndef OPENAIS_LOGGER_LOGLEVEL_H
#define OPENAIS_LOGGER_LOGLEVEL_H

#ifdef __cplusplus
namespace openais
{
	namespace logger
	{
#endif

enum LogLevel
{
	DEBUG = 0,
	NOTICE = 1,
	INFO = 2,
	WARN = 3,
	ERROR = 4,
	FATAL = 5
};

#ifdef __cplusplus
	}
}
#endif

#endif

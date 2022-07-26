#ifndef OPENAIS_LOGGER_LOG_H
#define OPENAIS_LOGGER_LOG_H

#include <Logger/LogLevel.h>

#ifdef __cplusplus
extern "C"
{
#endif
void log_entry(int level, const char *domain ...);
#ifdef __cplusplus
}
#endif

#define LOG_DEBUG(domain, ...) log_entry((int)openais::logger::DEBUG, domain, __VA_ARGS__);
#define LOG_NOTICE(domain, ...) log_entry((int)openais::logger::NOTICE, domain, __VA_ARGS__);
#define LOG_INFO(domain, ...) log_entry((int)openais::logger::INFO, domain, __VA_ARGS__);
#define LOG_WARN(domain, ...) log_entry((int)openais::logger::WARN, domain, __VA_ARGS__);
#define LOG_ERROR(domain, ...) log_entry((int)openais::logger::ERROR, domain, __VA_ARGS__);
#define LOG_FATAL(domain, ...) log_entry((int)openais::logger::FATAL, domain, __VA_ARGS__);

#endif


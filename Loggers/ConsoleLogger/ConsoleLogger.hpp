#ifndef OPENAIS_LOGGERS_CONSOLELOGGER
#define OPENAIS_LOGGERS_CONSOLELOGGER

#include <Logger/LogEntry.hpp>
#include <Task/Config.hpp>
#include <Logger/Logger.hpp>
#include <string>

#ifndef LOGGER_NAME
//This is usually defined at config time
#define LOGGER_NAME "Logger"
#endif

namespace openais {
	namespace logger {
		class ConsoleLogger: public Logger
		{
			private:
				//Used for self registering
				static ConsoleLogger _prototype;

			public:
				virtual void Log(LogEntryPtr entry)	override;
				virtual void Initialize(const task::Config &config) override;
				virtual std::string GetName() const override;

			public:
				ConsoleLogger(const ConsoleLogger &other);
				ConsoleLogger();
		};
	}
}

#endif

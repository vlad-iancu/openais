#ifndef OPENAIS_LOGGERS_CONSOLELOGGER
#define OPENAIS_LOGGERS_CONSOLELOGGER

#include <Logger/LogEntry.hpp>
#include <Task/Config.hpp>
#include <Logger/Logger.hpp>
#include <string>

namespace openais 
{
	namespace logger 
	{
		class ConsoleLogger: public Logger
		{
			private:
				//Used for self registering
				static ConsoleLogger _prototype;

			public:
				void Log(LogEntryPtr entry)	override;
				void Initialize(const task::Config &config) override;
				std::string GetName() const override;
			    void Clean() override;

			public:
				ConsoleLogger(const ConsoleLogger &other);
				ConsoleLogger();
		};
	}
}

#endif

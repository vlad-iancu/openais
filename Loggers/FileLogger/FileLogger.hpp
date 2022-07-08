#ifndef OPENAIS_LOGGERS_FILELOGGER
#define OPENAIS_LOGGERS_FILELOGGER

#include <Logger/Logger.hpp>
#include <fstream>
#include <mutex>

namespace openais 
{
	namespace logger 
	{
		class FileLogger: public Logger
		{
		private:
			static FileLogger _prototype;

		public:
			FileLogger();
			FileLogger(const FileLogger &other);

		public:
			void Log(LogEntryPtr entry) override;
			void Initialize(const Config &config) override;
			std::string GetName() const override;
			void Clean() override;
		
		private:
			int GetFileIndex() const;
			std::string GetCurrentLogFileName() const;
			void UpdateLogFile();
			void InitFileStream();
			void WriteMessage(const std::string &msg);

		private:
			std::string m_filePrefix;
			int m_fileIndex;
			std::FILE *m_file;
			std::size_t m_maxFileSize;
			std::size_t m_fileSize;
			std::mutex m_messageMutex;
			std::string m_dir;
		};
	}
}

#endif

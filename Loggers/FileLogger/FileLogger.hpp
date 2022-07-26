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
			/**
			 * @brief Logs an entry into the current file
			 */
			void Log(LogEntryPtr entry) override;

			/**
			 * @brief config contains the following fields:
			 * filePrefix: std::string -> The names of the generated log files will be in the form:
			 * 							  {config[filePrefix]}_{fileNumber}.log
			 * 	fileSize: 
			 */
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

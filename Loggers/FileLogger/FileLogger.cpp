#include <FileLogger.hpp>
#include <Task/Task.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <filesystem>
#include <mutex>
#include <iostream>
#include <ctime>

using namespace openais::logger;
FileLogger FileLogger::_prototype;

void FileLogger::Log(LogEntryPtr entry)
{
	std::scoped_lock<std::mutex> lk(m_messageMutex);	
	time_t t = (time_t)entry->GetTimeStamp();
	struct tm* utcTime;
	std::time(&t);
	utcTime = std::gmtime(&t);
	std::string logLevel = LogLevelToString(entry);
	std::string domain = entry->GetDomain();
	std::string message = entry->GetMessage();
	m_fileSize += std::fprintf(m_file, "(%ld) %04d-%02d-%02d %02d:%02d:%02d [%s] %s: %s\n",
				entry->GetTimeStamp(),
				utcTime->tm_year + 1900, utcTime->tm_mon + 1, utcTime->tm_mday,
				utcTime->tm_hour, utcTime->tm_min, utcTime->tm_sec,
				logLevel.c_str(), domain.c_str(), message.c_str()
			);
	UpdateLogFile();
}

void FileLogger::Initialize(const Config &config)
{
	m_filePrefix = config["filePrefix"].Get<std::string>(openais::task::Task::task->GetName());	
	m_maxFileSize = config["fileSize"].Get<int>(5 * 1024); //5KB by default
	m_dir = config["directory"].Get<std::string>();	
	m_fileIndex = GetFileIndex();
	InitFileStream();
}

std::string FileLogger::GetName() const
{
	return "FileLogger";
}

void FileLogger::WriteMessage(const std::string &msg)
{
	
}

int FileLogger::GetFileIndex() const
{
	namespace fs = std::filesystem;
	fs::path p(m_dir);
	std::error_code ec;
	bool created = fs::create_directories(p, ec);
	if(ec)
	{
		return -1;
	}
	fs::directory_iterator end_itr;
	boost::regex filePattern{m_filePrefix + "_([0-9])+\\.log"};
	int fileIndexMax = 0;
	bool isMaxFileAvailable = false;
	//for (fs::directory_iterator itr(p); itr != end_itr; ++itr)
	for(const fs::directory_entry &itr : fs::directory_iterator{p})
    {
        if (is_regular_file(itr.path())) 
		{
			boost::smatch what;
			if(boost::regex_search(itr.path().string(), what, filePattern))
			{
				std::string numMatch = what[1];
				int num = boost::lexical_cast<int>(numMatch);	
				if(num > fileIndexMax)
				{
					fileIndexMax = num;
					std::error_code ec;
					std::size_t fileSize = std::filesystem::file_size(itr.path(), ec);
					if(ec)
					{
						isMaxFileAvailable = false;
					}
					else
					{
						isMaxFileAvailable = fileSize < m_maxFileSize;
				 	}
				 }
			 }
		 }
	 }
    
	if(!isMaxFileAvailable || fileIndexMax == 0)
	{
		fileIndexMax++;
	}
	return fileIndexMax;
}

std::string FileLogger::GetCurrentLogFileName() const
{
	namespace fs = std::filesystem;
	std::string fileName = m_filePrefix + "_" + boost::lexical_cast<std::string>(std::max(m_fileIndex, 0)) + ".log";
	fs::path logDir(m_dir);
	logDir /= fileName;
	return logDir.string();
}

void FileLogger::Clean()
{
	std::fclose(m_file);				
}

void FileLogger::UpdateLogFile()
{
	if(m_fileSize < m_maxFileSize)
	{
		return;
	}
	std::filesystem::path logFilePath(GetCurrentLogFileName());
	std::error_code ec;
	m_fileIndex++;
	InitFileStream();
}

void FileLogger::InitFileStream()
{
	if(m_file != NULL)
	{
		std::fclose(m_file);
	}
	std::string fileName = GetCurrentLogFileName();
	std::filesystem::path p(fileName);
	std::error_code ec;
	std::size_t currentFileSize = std::filesystem::file_size(p, ec);
	if(ec)
	{
		currentFileSize = 0;
	}
	m_file = std::fopen(fileName.c_str(), "a+");
	m_fileSize = currentFileSize;
}

FileLogger::FileLogger()
{
	Logger::AddLogger(this);
}

FileLogger::FileLogger(const FileLogger &other)
{
	/*Empty*/
}

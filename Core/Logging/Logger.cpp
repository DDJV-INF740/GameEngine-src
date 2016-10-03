#include <Precompiled.h>
#include "Core/Logging/Logger.h"
#include <cstdarg>
#include <cstdio>
#include <map>
#include <string>

using namespace std;

namespace engine {

class LoggerConfig
{
public:
	using Level = Logger::Level;
public:
	LoggerConfig()
		: m_defaultLevel(Level::ALL)
	{}

	map<string, Logger*> m_loggers;
public:
	Level getLevel(const char *name)
	{
		return m_defaultLevel;
	}

	void setDefaultLevel(Level defaultLevel)
	{
		m_defaultLevel = defaultLevel;
	}

	void setLevel(const char *loggerName, Level level)
	{
		getLogger(loggerName)->setLevel(level);
	}

	Logger* getLogger(const char *loggerName)
	{
		auto found = m_loggers.find(loggerName);
		if (found != m_loggers.end())
			return found->second;

		Logger *logger = new Logger(getLevel(loggerName));
		m_loggers[loggerName] = logger;
		return logger;
	}

	Level m_defaultLevel;
};

LoggerConfig s_loggerConfig;

Logger* Logger::Get(const char *loggerName)
{
	return s_loggerConfig.getLogger(loggerName);
}

void Logger::SetDefaultLevel(Level defaultLevel)
{
	s_loggerConfig.setDefaultLevel(defaultLevel);
}

void Logger::SetLevel(const char *loggerName, Level defaultLevel)
{
	s_loggerConfig.setLevel(loggerName, defaultLevel);
}

static inline const char * Filename(const char *path)
{
	static const char kSeparator = '\\';

	const char *fileName = strrchr(path, kSeparator);
	if (fileName != nullptr)
		return fileName + 1;

	return path;
}


void Logger::DebugMacro(const char *filePath, int lineNumber, const char *str, ...)
{
	const char *fileName = Filename(filePath);
	Logger *logger = Get(fileName);
	logger->log(Level::DEBUG, "[%s:%d] ", fileName, lineNumber);
	va_list argptr;
	va_start(argptr, str);
	logger->log(Level::DEBUG, str, argptr);
	va_end(argptr);

	logger->log(Level::DEBUG, "\n");
}

void Logger::InfoMacro(const char *filePath, int lineNumber, const char *str, ...)
{
	const char *fileName = Filename(filePath);
	Logger *logger = Get(fileName);
	logger->log(Level::INFO, "[%s:%d] ", fileName, lineNumber);
	va_list argptr;
	va_start(argptr, str);
	logger->log(Level::INFO, str, argptr);
	va_end(argptr);

	logger->log(Level::INFO, "\n");
}

void Logger::WarnMacro(const char *filePath, int lineNumber, const char *str, ...)
{
	const char *fileName = Filename(filePath);
	Logger *logger = Get(fileName);
	logger->log(Level::WARN, "[%s:%d] ", fileName, lineNumber);
	va_list argptr;
	va_start(argptr, str);
	logger->log(Level::WARN, str, argptr);
	va_end(argptr);

	logger->log(Level::WARN, "\n");
}

void Logger::ErrorMacro(const char *filePath, int lineNumber, const char *str, ...)
{
	const char *fileName = Filename(filePath);
	Logger *logger = Get(fileName);
	logger->log(Level::ERROR, "[%s:%d] ", fileName, lineNumber);
	va_list argptr;
	va_start(argptr, str);
	logger->log(Level::ERROR, str, argptr);
	va_end(argptr);

	logger->log(Level::ERROR, "\n");
}

void Logger::FatalMacro(const char *filePath, int lineNumber, const char *str, ...)
{
	const char *fileName = Filename(filePath);
	Logger *logger = Get(fileName);
	logger->log(Level::FATAL, "[%s:%d] ", fileName, lineNumber);
	va_list argptr;
	va_start(argptr, str);
	logger->log(Level::FATAL, str, argptr);
	va_end(argptr);

	logger->log(Level::FATAL, "\n");
}


void Logger::log(Level level, const char *str, ...)
{
	va_list argptr;
	va_start(argptr, str);
	log(level, str, argptr);
	va_end(argptr);
}
void Logger::log(Level level, const char *str, va_list argptr)
{
	if (m_level < level)
		return;

	vfprintf(stderr, str, argptr);
}

void Logger::debug(const char *str, ...)
{
	va_list argptr;
	va_start(argptr, str);
	log(Level::DEBUG, str, argptr);
	log(Level::DEBUG, "\n");
	va_end(argptr);
}

void Logger::info(const char *str, ...)
{
	va_list argptr;
	va_start(argptr, str);
	log(Level::INFO, str, argptr);
	log(Level::INFO, "\n");
	va_end(argptr);
}

void Logger::warn(const char *str, ...)
{
	va_list argptr;
	va_start(argptr, str);
	log(Level::WARN, str, argptr);
	log(Level::WARN, "\n");
	va_end(argptr);
}

void Logger::error(const char *str, ...)
{
	va_list argptr;
	va_start(argptr, str);
	log(Level::ERROR, str, argptr);
	log(Level::ERROR, "\n");
	va_end(argptr);
}

void Logger::fatal(const char *str, ...)
{
	va_list argptr;
	va_start(argptr, str);
	log(Level::FATAL, str, argptr);
	log(Level::FATAL, "\n");
	va_end(argptr);
}


} // namespace engine
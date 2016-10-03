#pragma once

#ifdef DEBUG // from atldef.h
#undef DEBUG
#endif // TRACE

#ifdef ERROR
#undef ERROR
#endif // ERROR

namespace engine
{

#define ENGINE_LOGLEVEL_OFF 0
#define ENGINE_LOGLEVEL_FATAL 1
#define ENGINE_LOGLEVEL_ERROR 2
#define ENGINE_LOGLEVEL_WARN 3
#define ENGINE_LOGLEVEL_INFO 5
#define ENGINE_LOGLEVEL_DEBUG 6
#define ENGINE_LOGLEVEL_ALL 6

class Logger
{
public:
	enum class Level
	{
		OFF = ENGINE_LOGLEVEL_OFF,
		FATAL = ENGINE_LOGLEVEL_FATAL,
		ERROR = ENGINE_LOGLEVEL_ERROR,
		WARN = ENGINE_LOGLEVEL_WARN,
		INFO = ENGINE_LOGLEVEL_INFO,
		DEBUG = ENGINE_LOGLEVEL_DEBUG,
		ALL = ENGINE_LOGLEVEL_ALL
	};

public:
	Logger(Level level)
		: m_level(level)
	{}

	static Logger* Get(const char *loggerName);
	static void SetDefaultLevel(Level defaultLevel);
	static void SetLevel(const char *loggerName, Level defaultLevel);
	static void DebugMacro(const char *fileName, int lineNumber, const char *str, ...);
	static void InfoMacro(const char *fileName, int lineNumber, const char *str, ...);
	static void WarnMacro(const char *fileName, int lineNumber, const char *str, ...);
	static void ErrorMacro(const char *fileName, int lineNumber, const char *str, ...);
	static void FatalMacro(const char *fileName, int lineNumber, const char *str, ...);

	void log(Level level, const char *str, ...);
	void log(Level level, const char *str, va_list args);

	bool isDebugEnabled()
	{
		return m_level >= Level::DEBUG;
	}
	void debug(const char *str, ...);

	bool isInfoEnabled()
	{
		return m_level >= Level::INFO;
	}
	void info(const char *str, ...);


	bool isWarnEnabled()
	{
		return m_level >= Level::WARN;
	}
	void warn(const char *str, ...);

	bool isErrorEnabled()
	{
		return m_level >= Level::ERROR;
	}
	void error(const char *str, ...);

	bool isFatalEnabled()
	{
		return m_level >= Level::FATAL;
	}
	void fatal(const char *str, ...);

	void setLevel(Level level)
	{
		m_level = level;
	}

	Level getLevel()
	{
		return m_level;
	}

private:
	Level m_level;
};

#define ENGINE_LOGLEVEL ENGINE_LOGLEVEL_INFO

#if ENGINE_LOGLEVEL >= ENGINE_LOGLEVEL_DEBUG
#define LOG_DEBUG(_str, ...) do {Logger::DebugMacro(__FILE__, __LINE__, _str, ##__VA_ARGS__); } while (0)
#else
#define LOG_DEBUG(_str, ...) do {if (0) Logger::DebugMacro(__FILE__, __LINE__, _str, ##__VA_ARGS__); } while (0)
#endif
#if ENGINE_LOGLEVEL >= ENGINE_LOGLEVEL_INFO
#define LOG_INFO(_str, ...) do { Logger::InfoMacro(__FILE__, __LINE__, _str, ##__VA_ARGS__); } while(0)
#else
#define LOG_INFO(_str, ...) do {if (0) Logger::InfoMacro(__FILE__, __LINE__, _str, ##__VA_ARGS__);} while (0)
#endif
#if ENGINE_LOGLEVEL >= ENGINE_LOGLEVEL_WARN
#define LOG_WARN(_str, ...) do {Logger::WarnMacro(__FILE__, __LINE__, _str, ##__VA_ARGS__);} while (0)
#else
#define LOG_WARN(_str, ...) do { if (0) Logger::WarnMacro(__FILE__, __LINE__, _str, ##__VA_ARGS__); } while (0)
#endif
#if ENGINE_LOGLEVEL >= ENGINE_LOGLEVEL_ERROR
#define LOG_ERROR(_str, ...) do {Logger::ErrorMacro(__FILE__, __LINE__, _str, ##__VA_ARGS__);} while (0)
#else
#define LOG_ERROR(_str, ...) do { if (0) Logger::ErrorMacro(__FILE__, __LINE__, _str, ##__VA_ARGS__); } while (0)
#endif
#if ENGINE_LOGLEVEL >= ENGINE_LOGLEVEL_FATAL
#define LOG_FATAL(_str, ...) do {Logger::FatalMacro(__FILE__, __LINE__, _str, ##__VA_ARGS__);} while (0)
#else
#define LOG_FATAL(_str, ...) do { if (0) Logger::FatalMacro(__FILE__, __LINE__, _str, ##__VA_ARGS__); } while(0)
#endif
}

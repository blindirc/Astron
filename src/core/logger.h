#pragma once
#include <stdarg.h>

enum LogSeverity {
	LSEVERITY_SPAM,
	LSEVERITY_DEBUG,
	LSEVERITY_INFO,
	LSEVERITY_WARNING,
	LSEVERITY_SECURITY,
	LSEVERITY_ERROR,
	LSEVERITY_FATAL
};

class Logger {
public:
	void log(LogSeverity sev, const char *format, va_list va);
	void spam(const char *format, ...);
	void debug(const char *format, ...);
	void info(const char *format, ...);
	void warning(const char *format, ...);
	void security(const char *format, ...);
	void error(const char *format, ...);
	void fatal(const char *format, ...);
};

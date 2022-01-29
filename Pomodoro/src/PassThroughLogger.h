#pragma once

#include <stdarg.h>

// These warnings are for the windows CRT which has functions not available on the arduino
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

/// <summary>
/// Method used 
/// </summary>
typedef void (LogDelegate)(const char*);

/// <summary>
/// Simple class for formatting log messages and writing to a reciever
/// </summary>
class PassThroughLogger
{
public:
	PassThroughLogger(LogDelegate log)
	: log(log)
	{

	}

	void Log(const char* format, ...)
	{
		char formatBuffer[128];
		char buffer[128];

		// Decorate the format string with logger information
		snprintf(formatBuffer, sizeof(formatBuffer), "%s\n", format);
		va_list argp;
		va_start(argp, formatBuffer);
		vsnprintf(buffer, sizeof(buffer), formatBuffer, argp);
		va_end(argp);

		log(buffer);
	}

	void LogArray(const char* tag, const long * array, size_t count)
	{
		char buffer[128];
		size_t maxSize = sizeof(buffer);
		size_t pos = 0;

		// Copy the tag into the buffer, leaving room for a separator and null terminator
		if (tag)
		{
			strncpy(buffer, tag, maxSize - 2);
			pos = strnlen(buffer, maxSize - 2);

			buffer[pos++] = ':';
		}

		// Now add the array members
		for (size_t i = 0; pos < maxSize && i < count; i++) {
			int len = snprintf(buffer + pos, maxSize - pos, " 0x%08x", array[i]);
			pos += len;
		}

		// Ensure the buffer is null-terminated
		buffer[pos] = '\0';

		Log(buffer);
	}

private:
	LogDelegate* log;
};


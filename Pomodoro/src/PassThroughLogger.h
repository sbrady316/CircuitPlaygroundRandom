#pragma once

#include <stdarg.h>
#include <stdio.h>

// These warnings are for the windows CRT which has functions not available on the arduino
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

/// <summary>
/// Method used 
/// </summary>
typedef void (LogDelegate)(const char*);
class ILogSink
{
public:
	virtual void Log(const char* message) = 0;
};

/// <summary>
/// Simple class for formatting log messages and writing to a reciever
/// </summary>
class PassThroughLogger
{
public:
	PassThroughLogger(ILogSink& logSink)
	: logSink(logSink)
	{

	}

	void Log(const char* format, ...)
	{
		char buffer[BufferSize];

		// Decorate the format string with logger information
		va_list argp;
		va_start(argp, format);
		auto pos = vsnprintf(buffer, sizeof(buffer), format, argp);
		va_end(argp);

		// Add a trailing newline and terminator
		if (pos < 0)
		{
			pos = 0;
		}
		else if (pos > BufferSize - 2)
		{
			pos = BufferSize - 2;
		}
		
		buffer[pos++] = '\n';
		buffer[pos++] = '\0';

		logSink.Log(buffer);
	}

	void LogArray(uint32_t number, const unsigned long* array, size_t count)
	{
		char tag[20];
		snprintf(tag, sizeof(tag), "%8d", number);
		LogArray(tag, array, count);
	}

	/// <summary>
	/// Writes an array to the log
	/// </summary>
	/// <param name="tag">Optional tag about the array</param>
	/// <param name="array">The array to log</param>
	/// <param name="count">Number of elements in the array</param>
	void LogArray(const char* tag, const unsigned long * array, size_t count)
	{
		char buffer[BufferSize];
		size_t pos = 0;

		// Copy the tag into the buffer, leaving room for a separator and null terminator
		if (tag)
		{
			strncpy(buffer, tag, BufferSize - 2);
			pos = strnlen(tag, BufferSize - 2);

			buffer[pos++] = ':';
		}

		// Now add the array members
		for (size_t i = 0; pos < BufferSize && i < count; i++) {
			int len = snprintf(buffer + pos, BufferSize - pos, " 0x%08X", array[i]);
			pos += len;
		}

		// Ensure the buffer is null-terminated
		if (pos < 0)
		{
			pos = 0;
		}
		else if (pos > BufferSize - 1)
		{
			pos = BufferSize - 1;
		}
		buffer[pos] = '\0';

		Log(buffer);
	}

private:
	static constexpr size_t BufferSize = 128;
	ILogSink& logSink;
};


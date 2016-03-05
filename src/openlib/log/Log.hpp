/****************************************************************************
Copyright (c) 2016, OpenLib Project
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************************/
#pragma once

#include <string>
#include <chrono>
#include <stdexcept>
#include <mutex>

#include "../time/ElapsedTime.hpp"

#include "LogHandler.hpp"

namespace openlib {

/**
 * @brief Logging Utility
 *
 * Log::init(...) must be called before any instance of Log is created,
 * otherwise logging will be disable for those instances of Log.
 *
 * It is recommended to create one log object per module or class, that way
 * each module can have their own log level or sub tag as needed.
 */
class Log {
public:

  static const std::string TAG_NONE;    /**< Human readable tag for LogLevel::NONE */
  static const std::string TAG_FATAL;   /**< Human readable tag for LogLevel::FATAL */
  static const std::string TAG_ERROR;   /**< Human readable tag for LogLevel::ERROR */
  static const std::string TAG_WARN;    /**< Human readable tag for LogLevel::WARN */
  static const std::string TAG_INFO;    /**< Human readable tag for LogLevel::INFO */
  static const std::string TAG_VERBOSE; /**< Human readable tag for LogLevel::VERBOSE */
  static const std::string TAG_DEBUG;   /**< Human readable tag for LogLevel::DEBUG */
  static const std::string TAG_ALL;     /**< Human readable tag for LogLevel::ALL */

  /**
   * @brief Init the logging infrastructure
   * @param tag a human readable tag to be used for all instances of Log
   */
  static void init(const std::string& logTag);

  /**
   * @brief Init the logging infrastructure
   * @param tag a human readable tag to be used for all instances of Log
   * @param levelFilter log levels below this are ignored
   */
  static void init(const std::string& logTag, LogLevel levelFilter);

  /**
   * @brief Init the logging infrastructure
   * @param tag a human readable tag to be used for all instances of Log
   * @param logHandler a custom handler to output the logs
   */
  static void init(const std::string& logTag, const LogHandler *logHandler);

  /**
   * @brief Init the logging infrastructure
   * @param tag a human readable tag to be used for all instances of Log
   * @param levelFilter log levels below this are ignored
   * @param logHandler a custom handler to output the logs
   */
  static void init(const std::string& logTag, LogLevel levelFilter, const LogHandler *logHandler);

  /**
   * @brief Format a message using printf style variable argument lists
   * @param message printf style format string
   * @param ... arguments needed by message
   * @return a formatted message
   */
  static std::string format(const char* message, ...);

  /**
   * @brief get a human readable string for a given log level
   * @param level log level
   * @return a human readable string
   */
  static const std::string& levelStr(LogLevel level);

  /**
   * @brief Construct a log object using the default settings
   */
  Log();

  /**
   * @brief Construct a log object, overriding the default log level
   * @param levelFilter log levels below this are ignored
   */
  explicit Log(LogLevel levelFilter);

  /**
   * @brief Construct a log object, using a custom sub tag
   * @param subTag log messages will have an aditional sub tag
   */
  explicit Log(const std::string& subTag);

  /**
   * @brief Construct a log object, overriding the default log level and using a custom sub tag
   * @param levelFilter log levels below this are ignored
   * @param subTag log messages will have an aditional sub tag
   */
  explicit Log(LogLevel levelFilter, const std::string& subTag);

  /**
   * @brief Destructor
   */
  virtual ~Log() = default;

  /**
   * @brief get the current log level
   * @return current log level
   */
  virtual LogLevel level();

  /**
   * @brief set the log level
   * @param logLevel new log level
   */
  virtual void level(LogLevel logLevel);

  /**
   * @brief Log a fatal message
   * @param message to be logged
   */
  virtual void f(const std::string& message) const;

  /**
   * @brief Log a fatal message
   * @param message to be logged
   */
  virtual void fatal(const std::string& message) const;

  /**
   * @brief Log an error message
   * @param message to be logged
   */
  virtual void e(const std::string& message) const;

  /**
   * @brief Log an error message
   * @param message to be logged
   */
  virtual void error(const std::string& message) const;

  /**
   * @brief Log a warn message
   * @param message to be logged
   */
  virtual void w(const std::string& message) const;

  /**
   * @brief Log a warn message
   * @param message to be logged
   */
  virtual void warn(const std::string& message) const;

  /**
   * @brief Log an info message
   * @param message to be logged
   */
  virtual void i(const std::string& message) const;

  /**
   * @brief Log an info message
   * @param message to be logged
   */
  virtual void info(const std::string& message) const;

  /**
   * @brief Log a verbose message
   * @param message to be logged
   */
  virtual void v(const std::string& message) const;

  /**
   * @brief Log a verbose message
   * @param message to be logged
   */
  virtual void verbose(const std::string& message) const;

  /**
   * @brief Log a debug message
   * @param message to be logged
   */
  virtual void d(const std::string& message) const;

  /**
   * @brief Log a debug message
   * @param message to be logged
   */
  virtual void debug(const std::string& message) const;

  /**
   * @brief isLogging
   * Is this log object logging messages of this level?
   */
  virtual bool isLogging(LogLevel logLevel);

private:
  static const LogHandler *logHandler;
  static const ElapsedTime timestamp;

  static std::string globalTag;
  static LogLevel globalLevelFilter;
  static char globalFormatBuffer[];
  static std::mutex globalFormatBufferMutex;

  std::string logTag;
  LogLevel levelFilter;

  virtual void logMessage(LogLevel level, const std::string& message) const;
};

}

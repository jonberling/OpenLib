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
SERVICES {

} LOSS OF USE, DATA, OR PROFITS {

} OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
****************************************************************************/
#include <cstdarg>

#include "Log.hpp"
#include "LogHandler.hpp"

using namespace openlib;

const std::string UNKNOWN_LOG_LEVEL = "???";

const std::string Log::TAG_ALL     = "ALL";
const std::string Log::TAG_FATAL   = "FATAL";
const std::string Log::TAG_ERROR   = "ERROR";
const std::string Log::TAG_WARN    = "WARN";
const std::string Log::TAG_INFO    = "INFO";
const std::string Log::TAG_VERBOSE = "VERBOSE";
const std::string Log::TAG_DEBUG   = "DEBUG";
const std::string Log::TAG_NONE    = "NONE";

const LogHandler DEFAULT_LOG_HANDLER {};
const LogLevel DEFAULT_LOG_LEVEL = LogLevel::INFO;

const LogHandler* Log::logHandler = &DEFAULT_LOG_HANDLER;
const ElapsedTime Log::timestamp = ElapsedTime::createElapsedTime();

char Log::globalFormatBuffer[4 * 1024];
std::mutex Log::globalFormatBufferMutex;

std::string Log::globalTag = "LOG";
LogLevel Log::globalLevelFilter = LogLevel::NONE;

void Log::init(const std::string& tag) {
  init(tag, DEFAULT_LOG_LEVEL, &DEFAULT_LOG_HANDLER);
}

void Log::init(const std::string& tag, LogLevel levelFilter) {
  init(tag, levelFilter, &DEFAULT_LOG_HANDLER);
}

void Log::init(const std::string& tag, const LogHandler *logHandler) {
  init(tag, DEFAULT_LOG_LEVEL, logHandler);
}

void Log::init(const std::string& tag, LogLevel levelFilter, const LogHandler *logHandler) {
  Log::globalTag = tag;
  Log::globalLevelFilter = levelFilter;
  Log::logHandler = logHandler;
}

std::string Log::format(const char* message, ...) {
  std::lock_guard<std::mutex> lock(globalFormatBufferMutex);

  std::va_list arg;
  va_start(arg, message);
  std::vsnprintf(globalFormatBuffer, sizeof(globalFormatBuffer), message, arg);
  va_end(arg);
  return std::string(globalFormatBuffer);
}

const std::string& Log::levelStr(LogLevel level) {
  switch (level) {
    case LogLevel::NONE:    return TAG_NONE;
    case LogLevel::FATAL:   return TAG_FATAL;
    case LogLevel::ERROR:   return TAG_ERROR;
    case LogLevel::WARN:    return TAG_WARN;
    case LogLevel::INFO:    return TAG_INFO;
    case LogLevel::VERBOSE: return TAG_VERBOSE;
    case LogLevel::DEBUG:   return TAG_DEBUG;
    case LogLevel::ALL:     return TAG_ALL;
  }

  return UNKNOWN_LOG_LEVEL;
}

Log::Log():
    logTag(globalTag),
    levelFilter(globalLevelFilter) { }

Log::Log(LogLevel levelFilter):
    logTag(globalTag),
    levelFilter(levelFilter) { }

Log::Log(const std::string& subTag):
    logTag(globalTag + ": " + subTag),
    levelFilter(globalLevelFilter) { }

Log::Log(LogLevel levelFilter, const std::string& subTag):
    logTag(globalTag + ": " + subTag),
    levelFilter(levelFilter) { }

LogLevel Log::level() {
  return levelFilter;
}

void Log::level(LogLevel logLevel) {
  levelFilter = logLevel;
}

void Log::f(const std::string& message) const {
  fatal(message);
}
void Log::fatal(const std::string& message) const {
  logMessage(LogLevel::FATAL, message);
}

void Log::e(const std::string& message) const {
  error(message);
}
void Log::error(const std::string& message) const {
  logMessage(LogLevel::ERROR, message);
}

void Log::w(const std::string& message) const {
  warn(message);
}
void Log::warn(const std::string& message) const {
  logMessage(LogLevel::WARN, message);
}

void Log::i(const std::string& message) const {
  info(message);
}
void Log::info(const std::string& message) const {
  logMessage(LogLevel::INFO, message);
}

void Log::v(const std::string& message) const {
  verbose(message);
}
void Log::verbose(const std::string& message) const {
  logMessage(LogLevel::VERBOSE, message);
}

void Log::d(const std::string& message) const {
  debug(message);
}
void Log::debug(const std::string& message) const {
  logMessage(LogLevel::DEBUG, message);
}

bool Log::isLogging(LogLevel logLevel) {
  return level() <= logLevel;
}

void Log::logMessage(LogLevel level, const std::string& message) const {
  if (level < levelFilter) return;

  logHandler->logMessage(level, logTag, message, timestamp.time());
}

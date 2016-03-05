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
#include <cstring>

#include <gtest/gtest.h>

#include <openlib/log.hpp>

// if this is switched to 1, tests that print to stdout will
// be compiled in
#define RUN_TESTS_THAT_PRINT_TO_STDOUT 0

namespace openlibtest {

class MockLogHandler : public openlib::LogHandler {
public:

  mutable openlib::LogLevel level;
  mutable std::string tag;
  mutable std::string message;
  mutable double timestamp;

  MockLogHandler():
      level(openlib::LogLevel::DEBUG),
      tag(""),
      message(""),
      timestamp(0.0) {}

  virtual ~MockLogHandler() {}

  virtual void logMessage(openlib::LogLevel level, const std::string& tag, const std::string& message, double timestamp) const {
    this->level = level;
    this->tag = tag;
    this->message = message;
    this->timestamp = timestamp;
  }
};

}

using namespace openlibtest;

TEST(LogHandler, isConstructable) {
  openlib::LogHandler logHandler;
  // if the test gets this far it passes
}


TEST(Log, defaultsToLogLevelNoneWithoutInit) {
  openlib::Log log;
  log.fatal("YOU SHOULD NEVER SEE THIS LOG MESSAGE");
}

#if RUN_TESTS_THAT_PRINT_TO_STDOUT
TEST(Log, forceLogWithoutWithoutInit) {
  /*
   * For this test we need to see if we can force a log without calling init.
   * since we don't call init we can't override the default behavior.
   *
   * This will print to stdout
   */
  openlib::Log log(openlib::LogLevel::DEBUG);
  log.fatal("TEST LOG MESSAGE");
}

TEST(Log, printOneLogMessageOfEachType) {
  openlib::Log::init("TEST", openlib::LogLevel::ALL);
  openlib::Log log;

  log.f("test fatal message");
  log.e("test error message");
  log.w("test warn message");
  log.i("test info message");
  log.v("test verbose message");
  log.d("test debug message");
}
#endif // RUN_TESTS_THAT_PRINT_TO_STDOUT

TEST(Log, isConstructable) {
  openlib::Log::init("TEST");
  openlib::Log log;
  // if the test gets this far it passes
}

TEST(Log, format) {
  std::string a = openlib::Log::format("%s %s %s %d %d %d", "a", "b", "c", 1, 2, 3);
  std::string b = "a b c 1 2 3";
  EXPECT_EQ(a, b);
}

TEST(Log, fatal) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::ALL);

  log.f("test message");

  EXPECT_EQ(handler.level, openlib::LogLevel::FATAL);
}

TEST(Log, error) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::ALL);

  log.e("test message");

  EXPECT_EQ(handler.level, openlib::LogLevel::ERROR);
}

TEST(Log, warn) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::ALL);

  log.w("test message");

  EXPECT_EQ(handler.level, openlib::LogLevel::WARN);
}

TEST(Log, info) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::ALL);

  log.i("test message");

  EXPECT_EQ(handler.level, openlib::LogLevel::INFO);
}

TEST(Log, verbose) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::ALL);

  log.v("test message");

  EXPECT_EQ(handler.level, openlib::LogLevel::VERBOSE);
}

TEST(Log, debug) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::ALL);

  log.d("test message");

  EXPECT_EQ(handler.level, openlib::LogLevel::DEBUG);
}

TEST(Log, tag) {
  MockLogHandler handler;
  openlib::Log::init("TEST_TAG", &handler);
  openlib::Log log(openlib::LogLevel::ALL);

  log.d("test message");

  EXPECT_EQ(handler.tag, "TEST_TAG");
}

TEST(Log, message) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::ALL);

  log.d("test message");

  EXPECT_EQ(handler.message, "test message");
}

TEST(Log, messageAsCStr) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::ALL);

  char message[32];
  std::strcpy(message, "test message");

  log.d(message);

  EXPECT_EQ(handler.message, "test message");
}

TEST(Log, timestamp) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::ALL);

  log.d("test message");

  EXPECT_GE(handler.timestamp, 0.0);
}

TEST(Log, subTag) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::ALL, "TEST_SUB_TAG");

  log.d("test message");

  EXPECT_EQ(handler.tag, "TEST: TEST_SUB_TAG");
}

TEST(Log, logLevelFiler) {
  MockLogHandler handler;
  openlib::Log::init("TEST", openlib::LogLevel::INFO, &handler);
  openlib::Log log;

  log.d("test message");

  EXPECT_EQ(handler.message, ""); // empty message means no message was sent
}

TEST(Log, updateLogLevelFiler) {
  MockLogHandler handler;
  openlib::Log::init("TEST", openlib::LogLevel::INFO, &handler);
  openlib::Log log;

  log.d("test message");
  EXPECT_EQ(handler.message, ""); // empty message means no message was sent

  log.level(openlib::LogLevel::ALL);
  log.d("test message");
  EXPECT_EQ(handler.message, "test message");
}

TEST(Log, getLogLevelFiler) {
  MockLogHandler handler;
  openlib::Log::init("TEST", openlib::LogLevel::INFO, &handler);
  openlib::Log log;

  log.level(openlib::LogLevel::WARN);
  EXPECT_EQ(log.level(), openlib::LogLevel::WARN);
}

TEST(Log, isLogging) {
  MockLogHandler handler;
  openlib::Log::init("TEST", openlib::LogLevel::INFO, &handler);
  openlib::Log log;

  EXPECT_TRUE(log.isLogging(openlib::LogLevel::WARN));
  EXPECT_TRUE(log.isLogging(openlib::LogLevel::INFO));
  EXPECT_FALSE(log.isLogging(openlib::LogLevel::DEBUG));
}

TEST(Log, defaultLogLevelIsInfo) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log;

  log.d("test message");
  EXPECT_EQ(handler.message, ""); // empty message means no message was sent

  log.i("test message");
  EXPECT_EQ(handler.message, "test message");
}

TEST(Log, allLogsAll) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::ALL);

  log.d("debug test message");
  EXPECT_EQ(handler.message, "debug test message");

  log.f("fatal test message");
  EXPECT_EQ(handler.message, "fatal test message");
}

TEST(Log, noneLogsNone) {
  MockLogHandler handler;
  openlib::Log::init("TEST", &handler);
  openlib::Log log(openlib::LogLevel::NONE);

  log.d("debug test message");
  EXPECT_EQ(handler.message, ""); // empty message means no message was sent

  log.f("fatal test message");
  EXPECT_EQ(handler.message, ""); // empty message means no message was sent
}

TEST(Log, globalAllLogsAll) {
  MockLogHandler handler;
  openlib::Log::init("TEST", openlib::LogLevel::ALL, &handler);
  openlib::Log log;

  log.d("debug test message");
  EXPECT_EQ(handler.message, "debug test message");

  log.f("fatal test message");
  EXPECT_EQ(handler.message, "fatal test message");
}

TEST(Log, globalNoneLogsNone) {
  MockLogHandler handler;
  openlib::Log::init("TEST", openlib::LogLevel::NONE, &handler);
  openlib::Log log;

  log.d("debug test message");
  EXPECT_EQ(handler.message, ""); // empty message means no message was sent

  log.f("fatal test message");
  EXPECT_EQ(handler.message, ""); // empty message means no message was sent
}

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

#include "LogLevel.hpp"

namespace openlib {

/**
 * Logging Handler Utility
 *
 * Handles actual logging of the message. Override this class to get custom
 * logging behavior.
 */
class LogHandler {
  public:

  /**
   * @brief Constructor
   */
  LogHandler() = default;

  /**
   * @brief Destructor
   */
  virtual ~LogHandler() = default;

  /**
   * @brief Handles logging of messages
   * @param level level of message to log
   * @param tag tag of message to log
   * @param message contents of message to log
   * @param timestamp timestamp in ms since program started, of message to log
   *
   * If developing a custom log handler, override this method with your own logic.
   * Log::logLevelString(...) can be used to get a human readable string from a LogLevel
   */
  virtual void logMessage(LogLevel level, const std::string& tag, const std::string& message, double timestamp) const;
};

}

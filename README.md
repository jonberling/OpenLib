OpenLib, A C++ Open Library
===========================

How To Include This Library
---------------------------

If you want to build this as a stand alone project then use the `CMakeLists.txt` in the root folder.

If you want to build this as part of your existing project then include the `CMakeLists.txt` in the `src/openlib` folder. Then use `include_directories(${OPENLIB_INCLUDE_DIR})` in any CMake projects that you want to use it in.

To initialize the project, type `make` in the root directory.

Packages
========
* Array
  * Array
  * BufferArray
* Log
  * Log
  * LogHandler
  * LogLevel
* Math
  * Angle
  * Vector2d
* Time
  * ElapsedTime


Array
=====

Array
-----

Container that is between std::array and std::vector. Like std::vector, you can determine the size of the container at runtime. However, once the array is created it cannot be resized, and the underlying data structures will not move around in memory.

BufferArray
-----------

Container that convenient to use as a buffer. It contains methods to easily handle various primitive data types in the same BufferArray. The data is stored in network byte order, so the data can be reliably interchanged between systems with different endianess.

Log
===

Log
---

A logging utility class. It is designed to work stand alone, or alongside other logging utilities by implementing the LogHandler interface.

`Log::init(...)` must be called once before any log messages are generated, or logging will be disabled.

LogHandler
----------

The default LogHandler will send any log messages to stdout. However, you can implement the LogHandler interface and define any logging behavior.

The LogHandler interface has one method:

```C++
virtual void logMessage(
    LogLevel level,              // can vary from Error to Verbose
    const std::string& tag,      // tag of module generating log
    const std::string& message,  // log message
    double timestamp) const;     // timestamp; in seconds
```

As a sample of how to implement your own LogHandler, the default implementation is:

```C++
printf("[%-7s %s %8.03f] %s\n",
    Log::levelStr(level).c_str(),
    tag.c_str(),
    timestamp,
    message.c_str());
```

LogLevel
--------

These are the following log levels
* FATAL   - reserve for cases where the module will crash
* ERROR   - non-recoverable errors, module must exit or stop
* WARN    - warnings to the user, but module can continue
* INFO    - information the user might find useful
* VERBOSE - messages that most users will not find useful
* DEBUG   - messages only useful to the developers

There are additionally two levels that cannot be used as part of a message, but they are helpful in other cases, like filtering.

* ALL
* NONE

Math
====

Angle
-----

Acts like a double, but has helpful methods for dealing with angles. Uses radians.

Vector2d
--------

Model 2D vectors

Time
====

ElapsedTime
-----------

Track how much time has passed, in fractional seconds.

#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace Log
{

enum Level
{
  LEVEL_TRACE,
  LEVEL_VERBOSE,
  LEVEL_DEBUG,
  LEVEL_INFO,
  LEVEL_WARNING,
  LEVEL_ERROR,
  LEVEL_FATAL
};


struct LoggerSettings
{
 public:
  LoggerSettings(Level cutoff);

 public:
  Level cutoffLevel;
};
extern LoggerSettings loggerSettings;


class Logger
{
 public:
  Logger(Level level = LEVEL_DEBUG);
  virtual ~Logger();

  template <typename T>
  Logger& operator<< (const T& msg)
  {
    if (_level >= loggerSettings.cutoffLevel)
    {
      std::cout << msg;
      _opened = true;
    }

    return *this;
  }

 private:
  Level _level;
  bool _opened;

  inline std::string longLabel(Level level)
  {
    std::string sLabel;
    switch (level)
    {
      case LEVEL_TRACE:   sLabel = "TRACE";   break;
      case LEVEL_VERBOSE: sLabel = "VERBOSE"; break;
      case LEVEL_DEBUG:   sLabel = "DEBUG";   break;
      case LEVEL_INFO:    sLabel = "INFO";    break;
      case LEVEL_WARNING: sLabel = "WARNING"; break;
      case LEVEL_ERROR:   sLabel = "ERROR";   break;
      case LEVEL_FATAL:   sLabel = "FATAL";   break;

      default:            sLabel = "UNKNOWN"; break;
    }

    return sLabel;
  }

  inline char shortLabel(Level level)
  {
    char cLabel;
    switch (level)
    {
      case LEVEL_TRACE:   cLabel = 'T'; break;
      case LEVEL_VERBOSE: cLabel = 'V'; break;
      case LEVEL_DEBUG:   cLabel = 'D'; break;
      case LEVEL_INFO:    cLabel = 'I'; break;
      case LEVEL_WARNING: cLabel = 'W'; break;
      case LEVEL_ERROR:   cLabel = 'E'; break;
      case LEVEL_FATAL:   cLabel = 'F'; break;

      default:            cLabel = 'U'; break;
    }

    return cLabel;
  }
};

extern Logger TRACE();
extern Logger VERBOSE();
extern Logger DEBUG();
extern Logger INFO();
extern Logger WARNING();
extern Logger ERROR();
extern Logger FATAL();



} // namespace Log

#endif // LOGGER_H

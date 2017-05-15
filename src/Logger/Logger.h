#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

namespace Log
{

enum class Level
{
  VERBOSE,
  DEBUG,
  INFO,
  WARNING,
  ERROR,
  FATAL
};


class Logger
{
 public:
  Logger(Level level = Level::DEBUG) :
    _level(level),
    _opened(false)
  {
    std::cout << "[" << longLabel(level) << "] ";
  }

  virtual ~Logger()
  {
    if (_opened)
    {
      std::cout << std::endl;
    }

    _opened = false;
  }

  template <typename T>
  Logger& operator<< (const T& msg)
  {
    std::cout << msg;
    _opened = true;

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
      case Level::VERBOSE: sLabel = "VERBOSE"; break;
      case Level::DEBUG:   sLabel = "DEBUG";   break;
      case Level::INFO:    sLabel = "INFO";    break;
      case Level::WARNING: sLabel = "WARNING"; break;
      case Level::ERROR:   sLabel = "ERROR";   break;
      case Level::FATAL:   sLabel = "FATAL";   break;

      default:                sLabel = "UNKNOWN"; break;
    }

    return sLabel;
  }

  inline char shortLabel(Level level)
  {
    char cLabel;
    switch (level)
    {
      case Level::VERBOSE: cLabel = 'V'; break;
      case Level::DEBUG:   cLabel = 'D'; break;
      case Level::INFO:    cLabel = 'I'; break;
      case Level::WARNING: cLabel = 'W'; break;
      case Level::ERROR:   cLabel = 'E'; break;
      case Level::FATAL:   cLabel = 'F'; break;

      default:                cLabel = 'U'; break;
    }

    return cLabel;
  }
};



} // namespace Log

#endif // LOGGER_H

#include "Logger.h"

namespace Log
{

LoggerSettings::LoggerSettings(Level cutoff) :
  cutoffLevel(cutoff)
{
  // All the work is done in the initialization block.
}
LoggerSettings loggerSettings(LEVEL_VERBOSE);


Logger::Logger(Level level) :
  _level(level),
  _opened(false)
{
  if (level >= loggerSettings.cutoffLevel)
  {
    std::cout << "[" << longLabel(level) << "] ";
  }
}


Logger::~Logger()
{
  if (_opened)
  {
    std::cout << std::endl;
  }

  _opened = false;
}


Logger VERBOSE()
{
  return Logger(LEVEL_VERBOSE);
}


Logger DEBUG()
{
  return Logger(LEVEL_DEBUG);
}


Logger INFO()
{
  return Logger(LEVEL_INFO);
}


Logger WARNING()
{
  return Logger(LEVEL_WARNING);
}


Logger ERROR()
{
  return Logger(LEVEL_ERROR);
}


Logger FATAL()
{
  return Logger(LEVEL_FATAL);
}

} // namespace Log

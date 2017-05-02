#include "Logger.h"

#include <stdexcept>

const std::string Logger::VERBOSE  = "VERBOSE";
const std::string Logger::DEBUG    = "DEBUG";
const std::string Logger::INFO     = "INFO";
const std::string Logger::WARNING  = "WARNING";
const std::string Logger::ERROR    = "ERROR";
const std::string Logger::CRITICAL = "CRITICAL";

const char* const Logger::_logFilename = "log.txt";

Logger* Logger::_instance = nullptr;


Logger::Logger()
{
  _ostream.open(_logFilename, std::ios_base::out | std::ios_base::trunc);
  if (!_ostream.good())
  {
    throw std::runtime_error("Error: Unable to initialize the logger");
  }
}

Logger& Logger::instance()
{
  static LoggerCleanup cleanup;
  if (_instance == nullptr)
  {
    _instance = new Logger();
  }

  return *_instance;
}

Logger::LoggerCleanup::~LoggerCleanup()
{
  delete Logger::_instance;
  Logger::_instance = nullptr;
}

Logger::~Logger()
{
  _ostream.close();
}

void Logger::log(const std::string& level, const std::string& message)
{
  logHelper(level, message);
}

void Logger::log(const std::string& level,
    const std::vector< std::string >& messages)
{
  for (size_t i = 0; i < messages.size(); ++i)
  {
    logHelper(level, messages[i]);
  }
}

void Logger::logHelper(const std::string& level, const std::string& message)
{
  _ostream << "[" << level << "] " << message << std::endl;
  std::cout << "[" << level << "] " << message << std::endl;
}

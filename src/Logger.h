#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


class Logger
{
 public:
  static const std::string VERBOSE;
  static const std::string DEBUG;
  static const std::string INFO;
  static const std::string WARNING;
  static const std::string ERROR;
  static const std::string CRITICAL;

  static Logger& instance();

  void log(const std::string& level, const std::string& message);
  void log(const std::string& level,
      const std::vector< std::string >& messages);

 protected:
  static Logger *_instance;
  static const char* const _logFilename;
  std::ofstream _ostream;

  // Embedded class that handles the delete operation:
  friend class LoggerCleanup;
  class LoggerCleanup
  {
   public:
    ~LoggerCleanup();
  };

  void logHelper(const std::string& level, const std::string& message);

 private:
  Logger();
  virtual ~Logger();
  Logger(const Logger&);
  Logger& operator=(const Logger&);

};




#endif // LOGGER_H

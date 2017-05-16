#include <iostream>

namespace Log
{

template <typename T>
Logger& Logger::operator<< (const T& message)
{
  if (_level >= loggerSettings.cutoffLevel)
  {
    std::cout << message;
    _opened = true;
  }

  return *this;
}

} // namespace Log

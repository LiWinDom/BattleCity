#pragma once

#include <iostream>
#include <fstream>

#include "Path.h"

enum class LogOptions {
  None = 0,
  Console = 1,
  File = 1 << 1,
};

inline LogOptions operator|(const LogOptions& left, const LogOptions& right) {
  using T = std::underlying_type_t<LogOptions>;
  return static_cast<LogOptions>(static_cast<T>(left) | static_cast<T>(right));
}

inline LogOptions operator&(const LogOptions& left, const LogOptions& right) {
  using T = std::underlying_type_t<LogOptions>;
  return static_cast<LogOptions>(static_cast<T>(left) & static_cast<T>(right));
}

namespace Log {
  void message(const std::string& message, LogOptions options = LogOptions::Console | LogOptions::File) noexcept;

  void info(const std::string& message, const LogOptions options = LogOptions::Console | LogOptions::File);

  void debug(const std::string& message, const LogOptions options = LogOptions::Console | LogOptions::File);

  void warning(const std::string& message, const LogOptions options = LogOptions::Console | LogOptions::File);

  void error(const std::string& message, const LogOptions options = LogOptions::Console | LogOptions::File);
}

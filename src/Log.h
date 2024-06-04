#pragma once
#ifndef BATTLECITY_LOG_H
#define BATTLECITY_LOG_H

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

static std::ofstream clean(Path::getAbsolutePath("latest.log")); // Creating file, to start it over

namespace Log {
  static void message(const std::string& message, LogOptions options = LogOptions::Console | LogOptions::File) noexcept {
    if ((options & LogOptions::Console) != LogOptions::None) {
      std::cout << message << std::endl;
    }
    if ((options & LogOptions::File) != LogOptions::None) {
      std::ofstream file(Path::getAbsolutePath("latest.log"), std::ios::app);
      file << message << std::endl;
      file.close();
    }
  }

  static void info(const std::string& message, const LogOptions options = LogOptions::Console | LogOptions::File) {
    Log::message("[INFO] " + message, options);
  }

  static void warning(const std::string& message, const LogOptions options = LogOptions::Console | LogOptions::File) {
    Log::message("[WARNING] " + message, options);
  }

  static void error(const std::string& message, const LogOptions options = LogOptions::Console | LogOptions::File) {
    Log::message("[ERROR] " + message, options);
    throw std::runtime_error(message);
  }
}


#endif // BATTLECITY_LOG_H

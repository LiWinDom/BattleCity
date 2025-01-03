#include "Log.h"

static std::ofstream clean(Path::getAbsolutePath("latest.log")); // Creating file, to start it over

void Log::message(const std::string& message, LogOptions options) noexcept {
  if ((options & LogOptions::Console) != LogOptions::None) {
    std::cout << message << std::endl;
  }
  if ((options & LogOptions::File) != LogOptions::None) {
    std::ofstream file(Path::getAbsolutePath("latest.log"), std::ios::app);
    file << message << std::endl;
    file.close();
  }
}

void Log::info(const std::string& message, const LogOptions options) {
  Log::message("[INFO] " + message, options);
}

void Log::debug(const std::string& message, const LogOptions options) {
#ifdef DEBUG
  Log::message("[DEBUG] " + message, options);
#endif
}

void Log::warning(const std::string& message, const LogOptions options) {
  Log::message("[WARNING] " + message, options);
}

void Log::error(const std::string& message, const LogOptions options) {
  Log::message("[ERROR] " + message, options);
}

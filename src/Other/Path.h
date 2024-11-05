#pragma once

#include <string>

namespace Path {
  std::string getExecutablePath();
  std::string getExecutableDir();
  std::string mergePaths(const std::string& pathA, const std::string& pathB);
  std::string getAbsolutePath(const std::string& path);
}

#ifndef BATTLECITY_SERVER_PATH_H
#define BATTLECITY_SERVER_PATH_H

#include <string>

namespace Path {
  std::string getExecutablePath();
  std::string getExecutableDir();
  std::string mergePaths(const std::string& pathA, const std::string& pathB);
  std::string getAbsolutePath(const std::string& path);
  bool checkIfFileExists(const std::string& filePath);
}


#endif //BATTLECITY_SERVER_PATH_H

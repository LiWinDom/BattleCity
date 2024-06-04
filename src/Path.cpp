#include "Path.h"

#if defined(WIN32)
  #pragma comment(lib, "Shlwapi.lib")
  #include <windows.h>
  #include <Shlwapi.h>
  #include <io.h>
#endif

#ifdef APPLE
  #include <climits>
  #include <libgen.h>
  #include <mach-o/dyld.h>
  #include <unistd.h>
#endif

#ifdef LINUX
  #include <climits>
  #include <cstring>
  #include <libgen.h>
  #include <unistd.h>

  #if defined(__sun)
    #define PROC_SELF_EXE "/proc/self/path/a.out"
  #else
    #define PROC_SELF_EXE "/proc/self/exe"
  #endif
#endif

#if defined(WIN32)
  std::string Path::getExecutablePath() {
    char rawPathName[MAX_PATH];
    GetModuleFileNameA(NULL, rawPathName, MAX_PATH);
    return std::string(rawPathName);
  }

  std::string Path::getExecutableDir() {
    std::string executablePath = getExecutablePath();
    char* exePath = new char[executablePath.length()];
    strcpy(exePath, executablePath.c_str());
    PathRemoveFileSpecA(exePath);
    std::string directory = std::string(exePath);
    delete[] exePath;
    return directory;
  }

  std::string Path::mergePaths(const std::string& pathA, const std::string& pathB) {
    char combined[MAX_PATH];
    PathCombineA(combined, pathA.c_str(), pathB.c_str());
    std::string mergedPath(combined);
    return mergedPath;
  }
#endif

#ifdef LINUX
  std::string Path::getExecutablePath() {
    char rawPathName[PATH_MAX];
    realpath(PROC_SELF_EXE, rawPathName);
    return std::string(rawPathName);
  }

  std::string Path::getExecutableDir() {
    std::string executablePath = getExecutablePath();
    char *executablePathStr = new char[executablePath.length()];
    strcpy(executablePathStr, executablePath.c_str());
    char* executableDirStr = dirname(executablePathStr);
    std::string executableDir = std::string(executableDirStr);
    delete [] executablePathStr;
    return std::string(executableDir);
  }

  std::string Path::mergePaths(const std::string& pathA, const std::string& pathB) {
    return pathA + "/" + pathB;
  }
#endif

#ifdef APPLE
  std::string Path::getExecutablePath() {
    char rawPathName[PATH_MAX];
    char realPathName[PATH_MAX];
    uint32_t rawPathSize = (uint32_t)sizeof(rawPathName);

    if(!_NSGetExecutablePath(rawPathName, &rawPathSize)) {
      realpath(rawPathName, realPathName);
    }
    return  std::string(realPathName);
  }

  std::string Path::getExecutableDir() {
    std::string executablePath = getExecutablePath();
    char *executablePathStr = new char[executablePath.length() + 1];
    strcpy(executablePathStr, executablePath.c_str());
    char* executableDir = dirname(executablePathStr);
    delete [] executablePathStr;
    return std::string(executableDir);
  }

  std::string Path::mergePaths(const std::string& pathA, const std::string& pathB) {
    return pathA + "/" + pathB;
  }
#endif

std::string Path::getAbsolutePath(const std::string& path) {
  return Path::mergePaths(Path::getExecutableDir(), path);
}

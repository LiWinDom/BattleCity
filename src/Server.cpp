#include <iostream>

#include "Path.h"

int main() {
  std::cout << Path::getExecutableDir() << std::endl;
  std::cout << Path::getExecutablePath() << std::endl;
}
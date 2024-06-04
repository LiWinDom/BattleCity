#include <iostream>

#include "Path.h"

int main(int argc, char* argv[]) {
  std::cout << Path::getExecutableDir() << std::endl;
  std::cout << Path::getExecutablePath() << std::endl;
}
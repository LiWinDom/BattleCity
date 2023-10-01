BIN = bin
DEBUG = Debug
RELEASE = Release
RESOURCES = resources
CMAKE_BUILD_DEBUG = cmake-build-debug
CMAKE_BUILD_RELEASE = cmake-build-release
CMAKE_WINDOWS_RELEASE = cmake-windows-release
CMAKE_LINUX_RELEASE = cmake-linux-release
CMAKE_DARWIN_RELEASE = cmake-darwin-release

build:
	cmake -DCMAKE_BUILD_TYPE=Release -S ./ -B ./${CMAKE_BUILD_RELEASE}

debug:
	cmake -DCMAKE_BUILD_TYPE=Debug -S ./ -B ./${CMAKE_BUILD_DEBUG}

copy: dirs
	rm -rf ./$(BIN)/$(DEBUG)/$(RESOURCES)
	cp -r ./$(RESOURCES) ./$(BIN)/$(DEBUG)
	rm -rf ./$(BIN)/$(RELEASE)/$(RESOURCES)
	cp -r ./$(RESOURCES) ./$(BIN)/$(RELEASE)

win:
	cmake -DCMAKE_BUILD_TYPE=Release -S ./ -B ./${CMAKE_WINDOWS_RELEASE}

linux:
	cmake -DCMAKE_BUILD_TYPE=Release -S ./ -B ./${CMAKE_LINUX_RELEASE}

darwin:
	cmake -DCMAKE_BUILD_TYPE=Release -S ./ -B ./${CMAKE_DARWIN_RELEASE}

dirs:
	mkdir ./$(BIN)
	mkdir ./$(BIN)/$(DEBUG)
	mkdir ./$(BIN)/$(RELEASE)

clean:
	rm -rf ./$(BIN)

reload: clean
	rm -rf ./$(CMAKE_BUILD_DEBUG)
	rm -rf ./$(CMAKE_BUILD_RELEASE)
	rm -rf ./$(CMAKE_WINDOWS_RELEASE)
	rm -rf ./$(CMAKE_LINUX_RELEASE)
	rm -rf ./$(CMAKE_DARWIN_RELEASE)

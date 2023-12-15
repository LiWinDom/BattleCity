BIN = bin
DEBUG = Debug
RELEASE = Release
RESOURCES = resources
CMAKE_BUILD_WINDOWS = cmake-build-windows
CMAKE_BUILD_LINUX = cmake-build-linux
CMAKE_BUILD_DARWIN = cmake-build-darwin

dirs:
	mkdir ./$(BIN)
	mkdir ./$(BIN)/$(DEBUG)
	mkdir ./$(BIN)/$(RELEASE)

copy:
	rm -rf ./$(BIN)/$(DEBUG)/$(RESOURCES)
	cp -r ./$(RESOURCES) ./$(BIN)/$(DEBUG)
	rm -rf ./$(BIN)/$(RELEASE)/$(RESOURCES)
	cp -r ./$(RESOURCES) ./$(BIN)/$(RELEASE)

win32:
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_ARCHITECTURE=Win32 -S ./ -B ./${CMAKE_BUILD_WINDOWS}-Win32 -A Win32
	cmake --build ./${CMAKE_BUILD_WINDOWS}-Win32 --config Release

win64:
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_ARCHITECTURE=x64 -S ./ -B ./${CMAKE_WINDOWS_RELEASE}-x64 -A x64
	cmake --build ./${CMAKE_WINDOWS_RELEASE}-x64 --config Release

win: win32 win64

linux:
	cmake -DCMAKE_BUILD_TYPE=${RELEASE} -S ./ -B ./${CMAKE_BUILD_LINUX}
	+$(MAKE) -c ./${CMAKE_BUILD_LINUX}

darwin:
	cmake -DCMAKE_BUILD_TYPE=${RELEASE} -S ./ -B ./${CMAKE_BUILD_DARWIN}
	+$(MAKE) -c ./${CMAKE_BUILD_DARWIN}

clean:
	rm -rf ./$(BIN)

reload: clean
	rm -rf ./$(CMAKE_BUILD_WINDOWS)
	rm -rf ./$(CMAKE_BUILD_LINUX)
	rm -rf ./$(CMAKE_BUILD_DARWIN)

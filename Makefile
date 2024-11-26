BIN = bin
DEBUG = Debug
RELEASE = Release
RESOURCES = resources
CMAKE_BUILD_WINDOWS = cmake-build-windows
CMAKE_BUILD_LINUX = cmake-build-linux
CMAKE_BUILD_DARWIN = cmake-build-darwin

dirs:
	mkdir -p ./$(BIN)/$(DEBUG)/$(RESOURCES)
	mkdir -p ./$(BIN)/$(RELEASE)/$(RESOURCES)

win32:
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_ARCHITECTURE=Win32 -S ./ -B ./${CMAKE_BUILD_WINDOWS}-Win32 -A Win32
	cmake --build ./${CMAKE_BUILD_WINDOWS}-Win32 --config Release

win64:
	cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_BUILD_ARCHITECTURE=x64 -S ./ -B ./${CMAKE_BUILD_WINDOWS}-x64 -A x64
	cmake --build ./${CMAKE_BUILD_WINDOWS}-x64 --config Release

win: win32 win64

Windows : win

linux:
	cmake -DCMAKE_BUILD_TYPE=${RELEASE} -S ./ -B ./${CMAKE_BUILD_LINUX}
	cmake --build ./${CMAKE_BUILD_LINUX}

Linux: linux

darwin:
	cmake -DCMAKE_BUILD_TYPE=${RELEASE} -S ./ -B ./${CMAKE_BUILD_DARWIN}
	cmake --build ./${CMAKE_BUILD_DARWIN}

macOS: darwin

clean:
	rm -rf ./$(BIN)

reload: clean
	rm -rf ./$(CMAKE_BUILD_WINDOWS)
	rm -rf ./$(CMAKE_BUILD_LINUX)
	rm -rf ./$(CMAKE_BUILD_DARWIN)

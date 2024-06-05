cmake_minimum_required(VERSION 3.16)
set(CLIENT_PROJECT_NAME BattleCity-client)
set(SERVER_PROJECT_NAME BattleCity-server)
project(BattleCity LANGUAGES CXX)

set(CLIENT_VERSION "2024.603.1")
set(SERVER_VERSION "2024.603.1")

add_compile_definitions(CLIENT_VERSION="${CLIENT_VERSION}")
add_compile_definitions(SERVER_VERSION="${SERVER_VERSION}")

# Output directory
if (WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)
else ()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/${CMAKE_BUILD_TYPE})
endif ()

# Executables
set (
    CLIENT_EXECUTABLES ./src/Client.cpp
    ./src/Path.h ./src/Path.cpp
    ./src/Log.h ./src/Log.cpp
    ./src/IObject.h ./src/IObject.cpp
    ./src/Objects/ITank.h ./src/Objects/ITank.cpp
    ./src/Window.h ./src/Window.cpp
)
set (
    SERVER_EXECUTABLES ./src/Server.cpp
    ./src/Path.h ./src/Path.cpp
    ./src/Log.h ./src/Log.cpp
    ./src/IObject.h ./src/IObject.cpp
    ./src/Objects/ITank.h ./src/Objects/ITank.cpp
)

# Adding icon and other resources
file(GLOB_RECURSE RESOURCES "./resources/*")
foreach (FILE ${RESOURCES})
  file(RELATIVE_PATH NEW_FILE "${CMAKE_SOURCE_DIR}/resources" ${FILE})
  get_filename_component(NEW_FILE_PATH ${NEW_FILE} DIRECTORY)
  set_source_files_properties(${FILE} PROPERTIES MACOSX_PACKAGE_LOCATION "MacOS/resources/${NEW_FILE_PATH}")
  # Better to add to Resources folder, but it will break cross compilation
endforeach()
include(AddIconToBinary.cmake)
AddIconToBinary(RESOURCES ICONS ./resources/Icon.ico ./resources/Icon.icns)
if (WIN32)
  add_executable(${CLIENT_PROJECT_NAME} WIN32 ${CLIENT_EXECUTABLES} ${RESOURCES})
  add_executable(${SERVER_PROJECT_NAME} WIN32 ${SERVER_EXECUTABLES})
elseif (APPLE)
  add_executable(${CLIENT_PROJECT_NAME} MACOSX_BUNDLE ${CLIENT_EXECUTABLES} ${RESOURCES})
  add_executable(${SERVER_PROJECT_NAME} ${SERVER_EXECUTABLES})
else ()
  add_executable(${CLIENT_PROJECT_NAME} ${CLIENT_EXECUTABLES} ${RESOURCES})
  add_executable(${SERVER_PROJECT_NAME} ${SERVER_EXECUTABLES})
endif ()

# Adding defines
if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
  add_compile_definitions(RELEASE)
  set(RELEASE TRUE)
elseif (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_compile_definitions(DEBUG)
  set(DEBUG TRUE)
endif ()

if (WIN32)
  add_compile_definitions(WIN32)
elseif (LINUX)
  add_compile_definitions(LINUX)
elseif (APPLE)
  add_compile_definitions(APPLE)
endif ()

# Checking ethernet connection to be able to compile offline
if (WIN32)
  execute_process(
      COMMAND ping google.com -n 2
      ERROR_QUIET
      RESULT_VARIABLE NO_CONNECTION
  )
else ()
  execute_process(
      COMMAND ping google.com -c 2
      ERROR_QUIET
      RESULT_VARIABLE NO_CONNECTION
  )
endif ()

# FetchContent config
if (NO_CONNECTION GREATER 0)
  set(FETCHCONTENT_FULLY_DISCONNECTED ON)
  message(WARNING "Fetch offline mode: requires already populated _deps")
else ()
  set(FETCHCONTENT_FULLY_DISCONNECTED OFF)
endif ()
set(FETCHCONTENT_QUIET OFF)
include(FetchContent)

# Fetching SFML
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)

# Linking options
set(BUILD_SHARED_LIBS OFF)
if (APPLE)
  set(SFML_BUILD_FRAMEWORKS OFF)
  set_target_properties(${CLIENT_PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER LiWinDom.BattleCity.Client
    MACOSX_BUNDLE_BUNDLE_NAME ${CLIENT_PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${CLIENT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${CLIENT_VERSION}
  )
elseif (WIN32)
  if (RELEASE)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup") # Hiding console
  else ()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
  endif ()
  set(SFML_STATIC_LIBRARIES TRUE)
  set(SFML_USE_STATIC_STD_LIBS TRUE)
endif ()

# Set linked SFML libraries
set(CLIENT_SFML_LIBRARIES
    sfml-system
    sfml-graphics
    sfml-window
    # sfml-audio
    # sfml-network
)
set(SERVER_SFML_LIBRARIES
    sfml-system
    sfml-graphics
    # sfml-network
)

# Dont need yet
set(SFML_BUILD_AUDIO FALSE)
set(SFML_BUILD_NETWORK FALSE)

# Compiling SFML
FetchContent_MakeAvailable(SFML)
include_directories(${SFML_INCLUDE_DIR})

# Configuring executable
if (WIN32)
  set(ARCHITECTURE -${CMAKE_BUILD_ARCHITECTURE})
endif()

target_compile_features(${CLIENT_PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${CLIENT_PROJECT_NAME} PRIVATE ${CLIENT_SFML_LIBRARIES} ${LINK_FLAGS})
set_target_properties(${CLIENT_PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${CLIENT_PROJECT_NAME}-${CMAKE_SYSTEM_NAME}${ARCHITECTURE}"
    CLEAN_DIRECT_OUTPUT 1
)

target_compile_features(${SERVER_PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${SERVER_PROJECT_NAME} PRIVATE ${SERVER_SFML_LIBRARIES} ${LINK_FLAGS})
set_target_properties(${SERVER_PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${SERVER_PROJECT_NAME}-${CMAKE_SYSTEM_NAME}${ARCHITECTURE}"
    CLEAN_DIRECT_OUTPUT 1
)

# Copying resources folder
if (WIN32)
  file(COPY ./resources/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/resources/)
elseif (LINUX)
  file(COPY ./resources/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/)
endif()
# Copying OpenAL on Windows
if (WIN32)
  add_custom_command(
      TARGET ${CLIENT_PROJECT_NAME}
      COMMENT "Copy OpenAL DLL"
      PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${CLIENT_PROJECT_NAME}>
      VERBATIM)
endif()

install(TARGETS ${CLIENT_PROJECT_NAME} DESTINATION ./)
install(TARGETS ${SERVER_PROJECT_NAME} DESTINATION ./)

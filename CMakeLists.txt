cmake_minimum_required(VERSION 3.16)
set(CLIENT_PROJECT_NAME BattleCity-client)
set(SERVER_PROJECT_NAME BattleCity-server)
project(BattleCity LANGUAGES CXX)

# Executables
set(CLIENT_EXECUTABLES ./src/client.cpp)
set(SERVER_EXECUTABLES ./src/server.cpp)
if (WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/${CMAKE_BUILD_ARCHITECTURE})
else ()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/${CMAKE_BUILD_TYPE})
endif()

# Linking
set(CLIENT_SFML_LIBRARIES
    sfml-system
    sfml-graphics
    sfml-window
    # sfml-audio
    # sfml-network
)
set(SERVER_SFML_LIBRARIES
    sfml-system
    # sfml-network
)
set(BUILD_SHARED_LIBS OFF)

# Checking ethernet connection to be able to compile offline
if (WIN32)
  execute_process(
      COMMAND ping google.com -n 2
      ERROR_QUIET
      RESULT_VARIABLE NO_CONNECTION
  )
else()
  execute_process(
      COMMAND ping google.com -c 2
      ERROR_QUIET
      RESULT_VARIABLE NO_CONNECTION
  )
endif()
if (NO_CONNECTION GREATER 0)
  set(FETCHCONTENT_FULLY_DISCONNECTED ON)
  message(WARNING "Fetch offline mode: requires already populated _deps")
else()
  set(FETCHCONTENT_FULLY_DISCONNECTED OFF)
endif()

# Fetching SFML
include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)
include_directories(${SFML_INCLUDE_DIR})

# Adding executables
add_executable(${CLIENT_PROJECT_NAME} ${CLIENT_EXECUTABLES})
add_executable(${SERVER_PROJECT_NAME} ${SERVER_EXECUTABLES})

# It's recommended to build frameworks on MacOS
if(APPLE)
  set(SFML_BUILD_FRAMEWORKS TRUE)
elseif(WIN32)
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:CONSOLE")
  set(LINK_FLAGS -static)
  set(SFML_STATIC_LIBRARIES TRUE)
  set(SFML_USE_STATIC_STD_LIBS TRUE)
endif()

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

# Copying OpenAL on Windows
if (WIN32)
  set_target_properties(${CLIENT_PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
  add_custom_command(
      TARGET ${CLIENT_PROJECT_NAME}
      COMMENT "Copy OpenAL DLL"
      PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:${CLIENT_PROJECT_NAME}>
      VERBATIM)
endif()

install(TARGETS ${CLIENT_PROJECT_NAME})
install(TARGETS ${SERVER_PROJECT_NAME})

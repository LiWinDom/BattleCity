cmake_minimum_required(VERSION 3.16)
set(CLIENT_PROJECT_NAME BattleCity-client)
set(SERVER_PROJECT_NAME BattleCity-server)
project(${CLIENT_PROJECT_NAME} LANGUAGES CXX)
project(${SERVER_PROJECT_NAME} LANGUAGES CXX)

set(CLIENT_EXECUTABLES ./src/client.cpp)
set(SERVER_EXECUTABLES ./src/server.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/${CMAKE_BUILD_TYPE})

set(CLIENT_SFML_LIBRARIES
        sfml-system
        sfml-graphics
        sfml-window
        sfml-audio
        sfml-network
)
set(SERVER_SFML_LIBRARIES
        sfml-system
        sfml-network
)
set(BUILD_SHARED_LIBS OFF)

include(FetchContent)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
)
FetchContent_MakeAvailable(SFML)
include_directories(${SFML_INCLUDE_DIR})

add_executable(${CLIENT_PROJECT_NAME} ${CLIENT_EXECUTABLES})
add_executable(${SERVER_PROJECT_NAME} ${SERVER_EXECUTABLES})

if (APPLE)
    set(SFML_BUILD_FRAMEWORKS TRUE)
else()
    set(LINK_FLAGS -static)
endif()

target_compile_features(${CLIENT_PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${CLIENT_PROJECT_NAME} PRIVATE ${CLIENT_SFML_LIBRARIES} ${LINK_FLAGS})
set_target_properties(${CLIENT_PROJECT_NAME} PROPERTIES
        OUTPUT_NAME "${CLIENT_PROJECT_NAME}-${CMAKE_SYSTEM_NAME}"
        CLEAN_DIRECT_OUTPUT 1
)

target_compile_features(${SERVER_PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${SERVER_PROJECT_NAME} PRIVATE ${SERVER_SFML_LIBRARIES} ${LINK_FLAGS})
set_target_properties(${SERVER_PROJECT_NAME} PROPERTIES
        OUTPUT_NAME "${SERVER_PROJECT_NAME}-${CMAKE_SYSTEM_NAME}"
        CLEAN_DIRECT_OUTPUT 1
)

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

cmake_minimum_required(VERSION 3.13)
set(CLIENT_PROJECT_NAME BattleCity-client)
set(SERVER_PROJECT_NAME BattleCity-server)
project(BattleCity LANGUAGES CXX)

set(CLIENT_VERSION "2025.107.1")
set(SERVER_VERSION ${CLIENT_VERSION})

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
    SHARED_EXECUTABLES
    src/Other/Log.h src/Other/Log.cpp
    src/Other/Path.h src/Other/Path.cpp

    src/Game/Enums.h src/Game/Event.h
    src/Game/Game.h src/Game/Game.cpp
    src/Game/Network/Serializer.h src/Game/Network/Serializer.cpp
    src/Game/Objects/NetworkObject.h src/Game/Objects/NetworkObject.cpp

    src/Game/Objects/IMovable.cpp src/Game/Objects/IMovable.h
    src/Game/Objects/IObject.h src/Game/Objects/IObject.cpp

    src/Game/Objects/Interface/GameOver.h src/Game/Objects/Interface/GameOver.cpp
    src/Game/Objects/Interface/LeftTanks.h src/Game/Objects/Interface/LeftTanks.cpp
    src/Game/Objects/Interface/PlayerLives.h src/Game/Objects/Interface/PlayerLives.cpp
    src/Game/Objects/Interface/StageNumber.h src/Game/Objects/Interface/StageNumber.cpp

    src/Game/Objects/Playfield/Border.h src/Game/Objects/Playfield/Border.cpp
    src/Game/Objects/Playfield/Brick.h src/Game/Objects/Playfield/Brick.cpp
    src/Game/Objects/Playfield/Bush.h src/Game/Objects/Playfield/Bush.cpp
    src/Game/Objects/Playfield/Eagle.h src/Game/Objects/Playfield/Eagle.cpp
    src/Game/Objects/Playfield/EagleProtection.h src/Game/Objects/Playfield/EagleProtection.cpp
    src/Game/Objects/Playfield/IBlock.h src/Game/Objects/Playfield/IBlock.cpp
    src/Game/Objects/Playfield/TankSpawner.h src/Game/Objects/Playfield/TankSpawner.cpp
    src/Game/Objects/Playfield/Wall.h src/Game/Objects/Playfield/Wall.cpp
    src/Game/Objects/Playfield/Water.h src/Game/Objects/Playfield/Water.cpp

    src/Game/Objects/Tank/Bonus.h src/Game/Objects/Tank/Bonus.cpp
    src/Game/Objects/Tank/Bullet.h src/Game/Objects/Tank/Bullet.cpp
    src/Game/Objects/Tank/EnemyTank.h src/Game/Objects/Tank/EnemyTank.cpp
    src/Game/Objects/Tank/Explosion.h src/Game/Objects/Tank/Explosion.cpp
    src/Game/Objects/Tank/ITank.h src/Game/Objects/Tank/ITank.cpp
    src/Game/Objects/Tank/PlayerTank.h src/Game/Objects/Tank/PlayerTank.cpp
    src/Game/Objects/Tank/TankProtection.h src/Game/Objects/Tank/TankProtection.cpp
)
set (
    CLIENT_EXECUTABLES ./src/Client.cpp ${SHARED_EXECUTABLES}

    src/Game/Network/ClientNetwork.h src/Game/Network/ClientNetwork.cpp

    src/Game/Render/Window.h src/Game/Render/Window.cpp

    src/Game/Render/Drawables/IDrawable.h src/Game/Render/Drawables/IDrawable.cpp

    src/Game/Render/Drawables/Interface/GameOverDrawable.h src/Game/Render/Drawables/Interface/GameOverDrawable.cpp
    src/Game/Render/Drawables/Interface/LeftTanksDrawable.h src/Game/Render/Drawables/Interface/LeftTanksDrawable.cpp
    src/Game/Render/Drawables/Interface/PlayerLivesDrawable.h src/Game/Render/Drawables/Interface/PlayerLivesDrawable.cpp
    src/Game/Render/Drawables/Interface/StageNumberDrawable.h src/Game/Render/Drawables/Interface/StageNumberDrawable.cpp

    src/Game/Render/Drawables/Playfield/BorderDrawable.h src/Game/Render/Drawables/Playfield/BorderDrawable.cpp
    src/Game/Render/Drawables/Playfield/BrickDrawable.h src/Game/Render/Drawables/Playfield/BrickDrawable.cpp
    src/Game/Render/Drawables/Playfield/BushDrawable.h src/Game/Render/Drawables/Playfield/BushDrawable.cpp
    src/Game/Render/Drawables/Playfield/EagleDrawable.h src/Game/Render/Drawables/Playfield/EagleDrawable.cpp
    src/Game/Render/Drawables/Playfield/EagleProtectionDrawable.h src/Game/Render/Drawables/Playfield/EagleProtectionDrawable.cpp
    src/Game/Render/Drawables/Playfield/TankSpawnerDrawable.h src/Game/Render/Drawables/Playfield/TankSpawnerDrawable.cpp
    src/Game/Render/Drawables/Playfield/WallDrawable.h src/Game/Render/Drawables/Playfield/WallDrawable.cpp
    src/Game/Render/Drawables/Playfield/WaterDrawable.h src/Game/Render/Drawables/Playfield/WaterDrawable.cpp

    src/Game/Render/Drawables/Tank/BonusDrawable.h src/Game/Render/Drawables/Tank/BonusDrawable.cpp
    src/Game/Render/Drawables/Tank/BulletDrawable.h src/Game/Render/Drawables/Tank/BulletDrawable.cpp
    src/Game/Render/Drawables/Tank/ExplosionDrawable.h src/Game/Render/Drawables/Tank/ExplosionDrawable.cpp
    src/Game/Render/Drawables/Tank/TankDrawable.h src/Game/Render/Drawables/Tank/TankDrawable.cpp
    src/Game/Render/Drawables/Tank/TankProtectionDrawable.h src/Game/Render/Drawables/Tank/TankProtectionDrawable.cpp
)
set (
    SERVER_EXECUTABLES ./src/Server.cpp ${SHARED_EXECUTABLES}

    src/Game/Network/ServerNetwork.h src/Game/Network/ServerNetwork.cpp
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
if ("$ENV{FORCE_FETCH_CONTENT}" GREATER 0)
  set(NO_CONNECTION 0)
else ()
  if (WIN32)
    execute_process(
        COMMAND ping google.com -n 2
        OUTPUT_QUIET
        ERROR_QUIET
        RESULT_VARIABLE NO_CONNECTION
    )
  else ()
    execute_process(
        COMMAND ping google.com -c 2
        OUTPUT_QUIET
        ERROR_QUIET
        RESULT_VARIABLE NO_CONNECTION
    )
  endif ()
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
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} /MTd")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /MT")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  set(SFML_STATIC_LIBRARIES TRUE)
  set(SFML_USE_STATIC_STD_LIBS TRUE)
endif ()

# Set linked SFML libraries
set(CLIENT_SFML_LIBRARIES
    sfml-system
    sfml-graphics
    sfml-window
    # sfml-audio
    sfml-network
)
set(SERVER_SFML_LIBRARIES
    sfml-system
    sfml-network
)

# Dont need yet
set(SFML_BUILD_AUDIO FALSE)

# Compiling SFML
FetchContent_MakeAvailable(SFML)
include_directories(${SFML_INCLUDE_DIR})

# Fetching fmt library
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 8.1.1
)
FetchContent_MakeAvailable(fmt)

# Linking fmt library
target_link_libraries(${CLIENT_PROJECT_NAME} PRIVATE fmt::fmt)
target_link_libraries(${SERVER_PROJECT_NAME} PRIVATE fmt::fmt)

# Configuring executable
if (WIN32)
  set(ARCHITECTURE -${CMAKE_BUILD_ARCHITECTURE})
endif()

target_compile_features(${CLIENT_PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${CLIENT_PROJECT_NAME} PRIVATE ${CLIENT_SFML_LIBRARIES})
set_target_properties(${CLIENT_PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${CLIENT_PROJECT_NAME}-${CMAKE_SYSTEM_NAME}${ARCHITECTURE}"
    CLEAN_DIRECT_OUTPUT 1
)

target_compile_features(${SERVER_PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${SERVER_PROJECT_NAME} PRIVATE ${SERVER_SFML_LIBRARIES})
set_target_properties(${SERVER_PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "${SERVER_PROJECT_NAME}-${CMAKE_SYSTEM_NAME}${ARCHITECTURE}"
    CLEAN_DIRECT_OUTPUT 1
)

# Copying resources folder
if (WIN32)
  file(COPY ./resources/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/resources/)
  file(REMOVE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/resources/Icon.icns)
  file(REMOVE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/resources/Icon.ico)
  file(REMOVE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/resources/Icon.png)
elseif (LINUX)
  file(COPY ./resources/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources/)
  file(REMOVE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/resources/Icon.icns)
  file(REMOVE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/resources/Icon.ico)
  file(REMOVE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/resources/Icon.png)
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

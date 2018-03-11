cmake_minimum_required (VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

set( CMAKE_VERBOSE_MAKEFILE on )

project (MiniCard)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})


set (SRC 
    "src/Main.cpp" src/Styx.h src/Styx_RaylibImpl.cpp src/MiniCards.cpp src/Styx_RaylibImpl.h src/Styx.cpp src/MiniCards.h src/Game.cpp src/Game.h src/CardGame.cpp src/CardGame.h)

include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${RAYLIB_PATH}/raylib/release/include")
#include_directories(${OPENGL_INCLUDE_DIRS} ${OPENAL_INCLUDE_DIR})

if (EMSCRIPTEN)
    SET( CMAKE_EXE_LINKER_FLAGS "-s USE_GLFW=3 --preload-file ${PROJECT_SOURCE_DIR}/res@res/") #
    SET (LIBS_FILES "${RAYLIB_PATH}/raylib/release/libs/html5/libraylib.bc")
else(EMSCRIPTEN)
    link_directories(MiniCard "${RAYLIB_PATH}/raylib/release/libs/win32/mingw32/")
    SET (LIBS_FILES raylib OpenAL32 glfw3)
endif (EMSCRIPTEN)

add_executable(MiniCard ${SRC})
target_link_libraries(MiniCard ${LIBS_FILES})
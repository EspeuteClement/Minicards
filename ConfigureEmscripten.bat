cmake -Bbuildemscripten -H. -DEMSCRIPTEN=1 -DCMAKE_TOOLCHAIN_FILE=D:/Apps/emsdk/emscripten/1.37.22/cmake/Modules/Platform/Emscripten.cmake -DCMAKE_MODULE_PATH=D:/Apps/emsdk/emscripten/1.37.22/cmake/Modules -DCMAKE_BUILD_TYPE=RelWithDebInfo -G "Unix Makefiles" -DRAYLIB_PATH=C:/raylib
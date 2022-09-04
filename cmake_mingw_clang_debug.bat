powershell "rm -r ./build/debug"
cmake -B "build/debug" -G "MinGW Makefiles"  -D CMAKE_BUILD_TYPE="Debug" -D CMAKE_C_COMPILER="clang" -D CMAKE_CXX_COMPILER="clang++" -D CMAKE_CXX_FLAGS="-pthread -Wno-unused-private-field -Wthread-safety"
cmake --build "build/debug"
powershell "rm -r ./build/release"
cmake -B "build/release" -G "MinGW Makefiles"  -D CMAKE_BUILD_TYPE="Release" -D CMAKE_C_COMPILER="clang" -D CMAKE_CXX_COMPILER="clang++" -D CMAKE_CXX_FLAGS="-pthread -Wno-unused-private-field -Wthread-safety"
cmake --build "build/release"
powershell "rm -r ./build"
cmake -B build -G "Ninja" -D CMAKE_C_COMPILER=clang -D CMAKE_CXX_COMPILER=clang++ -D CMAKE_CXX_FLAGS=-pthread
cmake --build build
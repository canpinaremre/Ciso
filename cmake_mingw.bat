powershell "rm -r ./build"
cmake -B build -G "MinGW Makefiles"
cmake --build build
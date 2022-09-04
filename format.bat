for /R "./src/core" %%f in (*.cpp *.c *.h) do clang-format -style=file -i %%f
for /R "./src/drivers" %%f in (*.cpp *.c *.h) do clang-format -style=file -i %%f

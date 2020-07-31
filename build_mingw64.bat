mkdir build_mingw64
cd build_mingw64
set CC=x86_64-w64-mingw32-gcc.exe
set CXX=x86_64-w64-mingw32-g++.exe
@rem cmake -A x64 -G"Visual Studio 15 2017" .. 
cmake -G"MinGW Makefiles" .. 
pause
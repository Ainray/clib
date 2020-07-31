mkdir build_vs64
cd build_vs64
set CC=cl.exe
set CXX=cl.exe
cmake -A x64 -G"Visual Studio 15 2017" .. 
pause
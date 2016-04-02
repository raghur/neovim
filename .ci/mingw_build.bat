:: CMake/MinGW workaround, remove sh from PATH
set PATH=%PATH:C:\Program Files\Git\usr\bin;=%
:: Workaround for some MinGW toolchains
set CC=gcc
where sh
set PATH=C:\Qt\Tools\mingw492_32\bin\;%PATH%
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=..\INSTALL .. || goto :error
mingw32-make VERBOSE=1 || goto :error
bin\nvim.exe --version || goto :error

cd ..

goto :EOF
:error
exit /b %errorlevel%

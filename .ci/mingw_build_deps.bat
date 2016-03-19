:: CMake/MinGW workaround, remove sh from PATH
set PATH=%PATH:C:\Program Files\Git\usr\bin;=%
:: Workaround for some MinGW toolchains
set CC=gcc
where sh
set PATH=C:\Qt\Tools\mingw492_32\bin\;%PATH%
mkdir .deps
cd .deps
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..\third-party\ || goto :error
mingw32-make || goto :error
cd ..

goto :EOF
:error
exit /b %errorlevel%

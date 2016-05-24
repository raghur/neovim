:: sh.exe cannot be in PATH for MinGW builds
set PATH=%PATH:C:\msys64\usr\local\bin;=%
set PATH=%PATH:C:\msys64\usr\bin;=%
set PATH=%PATH:C:\msys64\bin;=%
set PATH=%PATH:C:\msys32\usr\local\bin;=%
set PATH=%PATH:C:\msys32\usr\bin;=%
set PATH=%PATH:C:\msys32\bin;=%
:: Remove these, otherwise luajit will treat this as MSYS2
set MSYSTEM=
set TERM=

mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..
if %errorlevel% neq 0 exit /b %errorlevel%
mingw32-make VERBOSE=1
if %errorlevel% neq 0 exit /b %errorlevel%

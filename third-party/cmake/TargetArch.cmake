# Set ${ARCHITECTURE} to the target arch
# either X86 or X86_64
include(CheckSymbolExists)

set(ARCHITECTURE NOTFOUND)
check_symbol_exists("_WIN32" "" T_WINDOWS)
if(T_WINDOWS)
  check_symbol_exists("_M_IX86" "" T_ARCH_X86)
  check_symbol_exists("_M_AMD64" "" T_ARCH_X64)
else()
  check_symbol_exists("__i386__" "" T_ARCH_X86)
  check_symbol_exists("__x86_64__" "" T_ARCH_X64)
endif()

if(T_ARCH_X86)
  set(ARCHITECTURE "X86")
elseif(T_ARCH_X64)
  set(ARCHITECTURE "X86_64")
endif()

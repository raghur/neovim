file(GLOB_RECURSE PRE_HEADERS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} pre/*.h)

foreach(hfile ${PRE_HEADERS})
  string(REGEX REPLACE ^pre/ post/ post_hfile ${hfile})
  get_filename_component(hdir ${CMAKE_CURRENT_BINARY_DIR}/${post_hfile} PATH)
  file(MAKE_DIRECTORY ${hdir})
  if(MSVC)
    add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${post_hfile}
      COMMAND ${CMAKE_C_COMPILER} /P
        ${CMAKE_CURRENT_SOURCE_DIR}/${hfile}
        /I${LIBUV_INCLUDE_DIRS}
	/Fi${CMAKE_CURRENT_BINARY_DIR}/${post_hfile})
  else()
    add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${post_hfile}
      COMMAND ${CMAKE_C_COMPILER} -std=c99 -E -P
        ${CMAKE_CURRENT_SOURCE_DIR}/${hfile}
        -I${LIBUV_INCLUDE_DIRS}
        -o ${CMAKE_CURRENT_BINARY_DIR}/${post_hfile})
  endif()
  list(APPEND POST_HEADERS ${post_hfile})
endforeach()

add_custom_target(unittest-headers DEPENDS ${POST_HEADERS})

# FFI headers used in lua tests - see cimport
set(FFI_HEADERS
  nvim/types.h
  nvim/main.h
  nvim/tempfile.h
  nvim/os/time.h
  nvim/os/os.h
  )

foreach(hfile ${FFI_HEADERS})
  file(WRITE "${PROJECT_BINARY_DIR}/ffi-mock-include.h" "#include <${hfile}>")

  set(post_hfile ${CMAKE_CURRENT_BINARY_DIR}/ffi-headers/${hfile})
  get_filename_component(hdir ${CMAKE_CURRENT_BINARY_DIR}/ffi-headers/${hfile} PATH)
  file(MAKE_DIRECTORY ${hdir})
  if(MSVC)
    add_custom_command(
      OUTPUT ${post_hfile}
      COMMAND ${CMAKE_C_COMPILER} /P
        /I${PROJECT_SOURCE_DIR}
        /I${PROJECT_SOURCE_DIR}/src
        /I${PROJECT_BINARY_DIR}/config
        /I${PROJECT_BINARY_DIR}/include
        /I${LIBUV_INCLUDE_DIRS}
        /DINCLUDE_GENERATED_DECLARATIONS
        "${PROJECT_BINARY_DIR}/ffi-mock-include.h"
        /Fi${post_hfile})
  else()
    add_custom_command(
      OUTPUT ${post_hfile}
      COMMAND ${CMAKE_C_COMPILER} -std=c99 -E -P
        -I${PROJECT_SOURCE_DIR}
        -I${PROJECT_SOURCE_DIR}/src
        -I${PROJECT_BINARY_DIR}/config
        -I${PROJECT_BINARY_DIR}/include
        -I${LIBUV_INCLUDE_DIRS}
        -D "aligned(ARGS)="
        -D "__attribute__(ARGS)="
        -D "__asm(ARGS)="
        -D "__asm__(ARGS)="
        -D "__inline__="
        -D "EXTERN=extern"
        -D "INIT(...)="
        -D_GNU_SOURCE'
        -DINCLUDE_GENERATED_DECLARATIONS
        # Needed for FreeBSD
        -D "_Thread_local="
        "${PROJECT_BINARY_DIR}/ffi-mock-include.h"
        -o ${post_hfile})
  endif()
  list(APPEND POST_FFI_HEADERS ${post_hfile})
endforeach()

add_custom_target(ffi-headers DEPENDS ${POST_FFI_HEADERS})


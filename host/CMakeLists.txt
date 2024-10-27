message(STATUS "null0: Building host: ${NULL0_HOST}")

if ("${HOST_TYPE}" STREQUAL "WEB" AND NOT EMSCRIPTEN)
    message(FATAL_ERROR "null0: Do not build for web, outside of emscritpen. Use emcmake or similar.")
endif()

# Use same files for host, but iwasm/retro is a DLL
if ("${HOST_TYPE}" STREQUAL "RETRO")
    add_library(${PROJECT_NAME}_libretro SHARED null0_entry.c null0_host.c)
elseif("${HOST_TYPE}" STREQUAL "IWASM")
    add_library(${PROJECT_NAME}_iwasm SHARED null0_entry.c null0_host.c)
else()
    add_executable(${PROJECT_NAME} null0_entry.c null0_host.c)
endif()

if ("${HOST_TYPE}" STREQUAL "RAYLIB")
    target_compile_definitions(${PROJECT_NAME} PUBLIC NULL0_BUILD_RAYLIB)
endif()

if ("${HOST_TYPE}" STREQUAL "SDL2")
    target_compile_definitions(${PROJECT_NAME} PUBLIC NULL0_BUILD_SDL2)
endif()

if ("${HOST_TYPE}" STREQUAL "RETRO")
    target_compile_definitions(${PROJECT_NAME}_libretro PUBLIC NULL0_BUILD_RETRO)
endif()

if ("${HOST_TYPE}" STREQUAL "IWASM")
    target_compile_definitions(${PROJECT_NAME}_iwasm PUBLIC NULL0_BUILD_IWASM)
endif()
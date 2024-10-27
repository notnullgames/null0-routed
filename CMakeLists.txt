cmake_minimum_required(VERSION 3.18)

project(null0
  DESCRIPTION "null0 game engine"
  HOMEPAGE_URL "https://github.com/konsumer/null0"
  VERSION 0.0.1
  LANGUAGES C
)

set(CMAKE_BUILD_TYPE Release)
cmake_policy(SET CMP0077 NEW)
# cmake_policy(SET CMP0135 NEW)

# everyone wants to make an "uninstall" target
set_property(GLOBAL PROPERTY ALLOW_DUPLICATE_CUSTOM_TARGETS 1)

include(FetchContent)
# set(FETCHCONTENT_QUIET OFF)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/tools/cmake")

# OPTIONS

# if they are building in emscripten, use WEB host
if(EMSCRIPTEN)
    set(NULL0_HOST "WEB" CACHE STRING "Native Host-type: RAYLIB/SDL2/RETRO")
endif()

# if they set a host-type, default to building it
if(NULL0_HOST)
    set(NULL0_BUILD_HOST ON CACHE BOOL "Build host?: ON/OFF")
endif()

option(NULL0_HOST "Native Host-type: RAYLIB/SDL2/RETRO" "RAYLIB")
option(CARTS "Build example carts: ON/OFF" OFF)
option(NULL0_BUILD_HOST "Build host?: ON/OFF" OFF)

if(NULL0_BUILD_HOST)
    message(STATUS "null0: Build host: ${NULL0_HOST}")
else()
    message(STATUS "null0: Build host: OFF")
endif()

if(CARTS)
    message(STATUS "null0: Build CARTS: ON")
else()
    message(STATUS "null0: Build CARTS: OFF")
endif()

# TODO; look into eum-validation for NULL0_HOST


# TARGETS

if(NULL0_BUILD_HOST)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/host)
endif()
if(CARTS)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/cart/c)
endif()


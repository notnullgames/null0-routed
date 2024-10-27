FetchContent_Declare(SDL2Source
  URL https://github.com/libsdl-org/SDL/archive/refs/tags/release-2.30.5.zip
)

FetchContent_MakeAvailable(SDL2Source)

set(SDL_SHARED  FALSE)
set(SDL2_SHARED  FALSE)
set(SDL_STATIC  TRUE)
set(SDL_TEST  FALSE)
set(SDL_TESTS  FALSE)
set(INTERFACE_SDL2_SHARED  FALSE)
set(SDL2_DISABLE_UNINSTALL  TRUE)
set(SDL2_DISABLE_INSTALL  TRUE)
set(SDL_INSTALL_TESTS  FALSE)
set(SDL2_LIBRARIES  SDL2::SDL2-static)

add_definitions(-DPNTR_APP_SDL -DPNTR_PIXELFORMAT_ARGB)
include_directories(${SDL2_INCLUDE_DIR}/..)

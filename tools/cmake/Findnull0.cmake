# handle different options
# CARTS=ON/OFF
# HOST_TYPE=OFF/WEB/RAYLIB/SDL/RETRO

if(EMSCRIPTEN)
  set(HOST_TYPE  "WEB")
  set(NULL0_HOST_TYPE_WEB  ON)
  # set(CARTS OFF)
else()
  set(NULL0_HOST_TYPE_WEB  OFF)
  option(CARTS "Build demo-carts" ON)
  if(NOT DEFINED HOST_TYPE)
    set(HOST_TYPE  "RAYLIB")
  endif()
  if("${HOST_TYPE}" STREQUAL "WEB")
    message(FATAL_ERROR "You must build WEB with emscripten (use emcmake)")
  endif()
endif()

message(STATUS "Null0 will built with the following options:")
if(CARTS)
  message(STATUS "  Example carts: ON")
else()
  message(STATUS "  Example carts: OFF")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/null0_api/src)

if(HOST_TYPE)
  message(STATUS "  Host: " ${HOST_TYPE})
  
  # setup easier booleans
  if("${HOST_TYPE}" STREQUAL "RAYLIB")
    set(NULL0_HOST_TYPE_RAYLIB  ON)
    set(NULL0_HOST_TYPE_SDL  OFF)
    set(NULL0_HOST_TYPE_RETRO  OFF)
  endif()

  if("${HOST_TYPE}" STREQUAL "SDL")
    set(NULL0_HOST_TYPE_RAYLIB  OFF)
    set(NULL0_HOST_TYPE_SDL  ON)
    set(NULL0_HOST_TYPE_RETRO  OFF)
  endif()

  if("${HOST_TYPE}" STREQUAL "WEB")
    set(NULL0_HOST_TYPE_RAYLIB  OFF)
    set(NULL0_HOST_TYPE_SDL  OFF)
    set(NULL0_HOST_TYPE_RETRO  OFF)
  endif()

  if("${HOST_TYPE}" STREQUAL "RETRO")
    set(NULL0_HOST_TYPE_RAYLIB  OFF)
    set(NULL0_HOST_TYPE_SDL  OFF)
    set(NULL0_HOST_TYPE_RETRO  ON)
  endif()

  option(NULL0_HOST_TYPE_RAYLIB "Build raylib host" ${NULL0_HOST_TYPE_RAYLIB})
  option(NULL0_HOST_TYPE_SDL "Build SDL host" ${NULL0_HOST_TYPE_SDL})
  option(NULL0_HOST_TYPE_RETRO "Build libretro-core host" ${NULL0_HOST_TYPE_RETRO})
  option(NULL0_HOST_TYPE_WEB "Build web-host" ${NULL0_HOST_TYPE_WEB})

  if(NOT NULL0_HOST_TYPE_WEB AND NOT NULL0_HOST_TYPE_RAYLIB AND NOT NULL0_HOST_TYPE_SDL AND NOT NULL0_HOST_TYPE_RETRO)
    message(FATAL_ERROR "Invalid HOST_TYPE: (${HOST_TYPE}) choose OFF, WEB, RAYLIB, SDL, or RETRO")
  endif()

  if (NULL0_HOST_TYPE_SDL)
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
    #set(SDL2_LIBRARIES SDL2::SDL2 SDL2::SDL2main)

    # SDL_mixer
    set(SDL2MIXER_VORBIS  STB)
    set(SDL2MIXER_INSTALL  OFF)
    set(SDL2MIXER_DEPS_SHARED  OFF)
    set(SDL2MIXER_VENDORED  OFF)
    set(SDL2MIXER_SAMPLES  OFF)
    set(SDL2MIXER_CMD  OFF)
    set(SDL2MIXER_FLAC  OFF)
    set(SDL2MIXER_MOD  OFF)
    set(SDL2MIXER_MP3  OFF)
    set(SDL2MIXER_MIDI_NATIVE  OFF)
    set(SDL2MIXER_OPUS  OFF)
    set(SDL2MIXER_OPUS_SHARED  OFF)
    set(SDL2MIXER_MIDI_FLUIDSYNTH  OFF)
    set(SDL2MIXER_MP3_MPG123  OFF)
    set(SDL2MIXER_MP3_DRMP3  OFF)
    set(SDL2MIXER_MOD_XMP  OFF)
    set(SDL2MIXER_MOD_MODPLUG  OFF)
    set(SDL2MIXER_FLAC_DRFLAC  OFF)
    set(SDL2MIXER_FLAC_LIBFLAC  OFF)
    set(SDL2MIXER_VORBIS_VORBISFILE  OFF)
    set(SDL2MIXER_WAVPACK  OFF)
    set(SDL2MIXER_SAMPLES_INSTALL  OFF)
    set(SDL2MIXER_BUILD_SHARED_LIBS  OFF)

    find_package(SDL2 REQUIRED)
    find_package(SDL2_mixer REQUIRED)

    add_definitions(-DPNTR_APP_SDL -DPNTR_PIXELFORMAT_ARGB)
    include_directories(${SDL2_INCLUDE_DIR}/..)
  endif()

  if (NULL0_HOST_TYPE_RAYLIB)
    add_definitions(-DPNTR_NO_STB_IMAGE_IMPLEMENTATION)
    add_definitions(-DPNTR_NO_STB_IMAGE_WRITE_IMPLEMENTATION)
    find_package(raylib REQUIRED)
    add_definitions(-DPNTR_APP_RAYLIB -DPNTR_PIXELFORMAT_RGBA)
  endif()

  if (NULL0_HOST_TYPE_WEB)
    add_definitions(-DPNTR_APP_WEB -DPNTR_PIXELFORMAT_RGBA)
  else()
    find_package(wamr REQUIRED)
    add_library(vmlib ${WAMR_RUNTIME_LIB_SOURCE})
  endif()

  if (NULL0_HOST_TYPE_RETRO)
    add_definitions(-DPNTR_APP_LIBRETRO -DPNTR_PIXELFORMAT_ARGB)
    find_package(libretrocommon)
  endif()

  set(PHYSFS_ARCHIVE_7Z CACHE INTERNAL FALSE)
  set(PHYSFS_ARCHIVE_GRP CACHE INTERNAL FALSE)
  set(PHYSFS_ARCHIVE_HOG CACHE INTERNAL FALSE)
  set(PHYSFS_ARCHIVE_ISO9660 CACHE INTERNAL FALSE)
  set(PHYSFS_ARCHIVE_MVL CACHE INTERNAL FALSE)
  set(PHYSFS_ARCHIVE_QPAK CACHE INTERNAL FALSE)
  set(PHYSFS_ARCHIVE_SLB CACHE INTERNAL FALSE)
  set(PHYSFS_ARCHIVE_VDF CACHE INTERNAL FALSE)
  set(PHYSFS_ARCHIVE_CSM CACHE INTERNAL FALSE)
  set(PHYSFS_ARCHIVE_WAD CACHE INTERNAL FALSE)
  set(PHYSFS_BUILD_STATIC TRUE)
  set(PHYSFS_BUILD_SHARED CACHE INTERNAL FALSE)
  set(PHYSFS_BUILD_TEST CACHE INTERNAL FALSE)
  set(PHYSFS_BUILD_DOCS CACHE INTERNAL FALSE)
  set(PHYSFS_DISABLE_INSTALL CACHE INTERNAL TRUE)

  find_package(pntr REQUIRED)
  find_package(pntr_app REQUIRED)
  find_package(pntr_app_sfx REQUIRED)
  find_package(physfs REQUIRED)

  add_subdirectory(null0_api)
  add_subdirectory(host)
else()
  message(STATUS "  Host: OFF")
endif()

if (CARTS)
  add_subdirectory(cart/c)
endif()
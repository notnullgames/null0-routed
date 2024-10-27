# test if vars work here
if(NULL0_BUILD_HOST)
    message(STATUS "null0: Building host: ${NULL0_HOST}")

    if (NULL0_BUILD_HOST AND "${HOST_TYPE}" STREQUAL "WEB" AND NOT EMSCRIPTEN)
        message(FATAL_ERROR "null0: Do not build for web, outside of emscritpen. Use emcmake.")
    endif()

    

else()
    message(STATUS "null0: Not building host")
endif()



FetchContent_Declare(pntr_app
  URL https://github.com/RobLoach/pntr_app/archive/refs/heads/master.zip
)
FetchContent_MakeAvailable(pntr_app)
include_directories(${pntr_app_SOURCE_DIR}/include)

# CMakeList.txt : CMake project for SnakeCMake, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (SnakeCMake "src/state.c" "src/state.h" "src/main.c" "src/main.h" "src/globals.h" "src/screen.h" "src/screen.c" "src/input.h" "src/input.c")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SnakeCMake PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.

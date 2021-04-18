# make a build file for the emualtor

#cmake_minimum_required(VERSION 3.10) # miniumum version
cmake_minimum_required (VERSION 2.6)
project (chip8buildtool)


# compiler flags for debugging
SET(GCC_COVERAGE_COMPILE_FLAGS "-g") # -g builds a special debug version that works with GDB
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

# sub folders for souce and header files
#add_subdirectory(headers)
#add_subdirectory(source)

# sets for header and souce files
set(HEADER_FILES
  ./asm8header.h
  ./disass8header.h
)

set(SOURCE_FILES
  ./main.cpp
  ./asm8build.cpp
  ./ch8disassembler.cpp
)

add_executable(chip8builder
	${HEADER_FILES}
	${SOURCE_FILES}
)

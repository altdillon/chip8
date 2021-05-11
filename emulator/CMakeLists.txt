
cmake_minimum_required (VERSION 2.6)
project (Chip8emulator)


# compiler flags for debugging
SET(GCC_COVERAGE_COMPILE_FLAGS "-g -Wall")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

set(MY_HEADER_FILES
  ./chip8sys.h
  ./chip8emucfg.h
)

set(MY_SOURCE_FILES
	./chip8main.cpp
  ./chip8binfile.cpp
  ./chip8ram.cpp
)

add_executable(chip8emu
	${MY_HEADER_FILES}
	${MY_SOURCE_FILES}
)

#target_link_libraries(glut2dTest
#    OpenGL::GL
#    OpenGL::GLU
#    GLUT::GLUT
#    GLEW::GLEW
#)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
target_link_libraries(chip8emu ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )

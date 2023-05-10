cmake_minimum_required(VERSION 3.6)
project(ProjectSoftwareEngineer)

set(CMAKE_VERBOSE_MAKEFILE ON)

set(CMAKE_CXX_STANDARD 98)
set(CMAKE_CXX_FLAGS "-std=c++98 -Wall -Werror -O2")
set(CMAKE_EXE_LINKER_FLAGS -pthread)

# Set include dir
include_directories(./gtest/include)

# Set Library dir
link_directories(./gtest/lib)

# Set source files for RELEASE target
set(RELEASE_SOURCE_FILES
        src/main.cpp
        tinyxml/tinyxml.cpp
        tinyxml/tinystr.cpp
        tinyxml/tinyxmlerror.cpp
        tinyxml/tinyxmlparser.cpp
        src/Systeem.cpp
        src/Tram.cpp
        src/Station.cpp
        src/DesignByContract.h
        src/simulationUtils.cpp src/MetroReader.cpp src/MetroReader.h src/MetroOutput.cpp src/MetroOutput.h)

# Set source files for DEBUG target
set(DEBUG_SOURCE_FILES
        src/DesignByContract.h
        src/tests.cpp
        src/testInput.h
        src/Tram.cpp
        src/Station.cpp
        src/Systeem.cpp
        src/testTram.h
        src/testPCC.h
        tinyxml/tinyxml.cpp
        tinyxml/tinystr.cpp
        tinyxml/tinyxmlerror.cpp
        tinyxml/tinyxmlparser.cpp
        src/testStation.h
        src/testSysteem.h
        src/simulationUtils.cpp
        src/testOutput.h
        src/MetroReader.cpp
        src/MetroOutput.cpp)

# Create RELEASE target
add_executable(ttt ${RELEASE_SOURCE_FILES})

# Create DEBUG target
add_executable(ttt_debug ${DEBUG_SOURCE_FILES})

# Link library
target_link_libraries(ttt_debug gtest)
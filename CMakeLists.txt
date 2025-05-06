cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
# Force g++
set(CMAKE_CXX_COMPILER g++)
#set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project(interval_map)
include_directories(include)

add_library(mylib INTERFACE)
target_include_directories(mylib INTERFACE include)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} mylib)

enable_testing()
add_subdirectory(test)

# install(TARGETS ${PROJECT_NAME} DESTINATION bin) 
#optional:  sudo make install    (create binary in  /usr/<local>/bin/ )

# run:   cmake -S . -B build

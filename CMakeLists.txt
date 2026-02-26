cmake_minimum_required(VERSION 3.15)
project(Huffman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(wxWidgets_ROOT_DIR $ENV{WXWIN})
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(Huffman WIN32 ${SOURCES})

target_include_directories(Huffman PRIVATE src)
target_link_libraries(Huffman ${wxWidgets_LIBRARIES})
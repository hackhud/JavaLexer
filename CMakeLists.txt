cmake_minimum_required(VERSION 3.10)
project(Lexer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(Lexer ${SOURCES})
if(WIN32)
    target_link_libraries(Lexer -static -static-libgcc -static-libstdc++)
endif()

if(UNIX)
    target_compile_options(java_lexer PRIVATE -Wall -Wextra)
endif()
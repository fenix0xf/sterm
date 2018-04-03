#
# MIT License
#
# Copyright (c) 2018 Alexander Kotikov <alexandr.kotikov@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(sterm CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CXX_WARNINGS
    -Werror
    -Wall
    -Wextra
    -Wpedantic
    -Wconversion
    -Wshadow
    -Wno-unused-function
    -Wno-unused-parameter
    -Wnon-virtual-dtor)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

file(GLOB SOURCES RELATIVE ${CMAKE_SOURCE_DIR} src/*.[h,c]pp)

set(TARGET_NAME sterm)

add_executable(${TARGET_NAME} ${SOURCES})

target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/lib/fmt/include)
target_compile_options(${TARGET_NAME} PUBLIC ${CXX_WARNINGS})

add_subdirectory(lib/fmt)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

target_link_libraries(${TARGET_NAME} Qt5::Widgets fmt)

### Update BuildDate.hpp file for all targets.
add_custom_target(__build_date_target COMMAND ${PROJECT_SOURCE_DIR}/build-date.py ../src/BuildDate.hpp)
add_dependencies(${TARGET_NAME} __build_date_target)

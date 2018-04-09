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

set(TARGET_NAME sterm)

file(GLOB SOURCES RELATIVE ${CMAKE_SOURCE_DIR} src/*.[h,c]pp)

if (UNIX AND NOT APPLE)
    message(">>> Linux build <<<")
    file(GLOB PLATFORM_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} src/*.Linux.[h,c]pp)
elseif (APPLE)
    message(FATAL_ERROR "Apple platform is not supported!")
    #    message(">>> MacOS build <<<")
    #    file(GLOB PLATFORM_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} src/*.MacOS.[h,c]pp)
elseif (WIN32)
    message(FATAL_ERROR "Windows platform is not supported!")
    #    message(">>> Windows build <<<")
    #    file(GLOB PLATFORM_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} src/*.Windows.[h,c]pp)
endif ()

add_executable(${TARGET_NAME} ${SOURCES} ${PLATFORM_SOURCES})

target_include_directories(${TARGET_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/lib/fmt/include)
target_compile_options(${TARGET_NAME} PUBLIC ${CXX_WARNINGS})
target_compile_definitions(${TARGET_NAME} PUBLIC $<$<CONFIG:Debug>:DEBUG>)

add_subdirectory(lib/fmt)
find_package(Qt5 COMPONENTS Widgets SerialPort REQUIRED)

target_link_libraries(${TARGET_NAME} Qt5::Widgets Qt5::SerialPort fmt)

add_custom_target(__build_info_target COMMAND ${PROJECT_SOURCE_DIR}/build-info.py ../src/BuildInfo.hpp)
add_dependencies(${TARGET_NAME} __build_info_target)

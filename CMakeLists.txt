cmake_minimum_required(VERSION 3.10)

project(sterm CXX)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

aux_source_directory(src SOURCES)

add_executable(sterm ${SOURCES})

find_package(Qt5 COMPONENTS Widgets DBus REQUIRED)
target_link_libraries(sterm Qt5::Widgets Qt5::DBus)

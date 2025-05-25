cmake_minimum_required(VERSION 3.16)

project(test VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

# 源码文件（src 目录下）
set(PROJECT_SOURCES
    src/main.cpp
    src/simple_app.cc
    src/simple_app.h
    src/simple_handler.cc
    src/simple_handler.h
)

add_executable(test
    ${PROJECT_SOURCES}
)

# 头文件包含路径
target_include_directories(test PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/cef
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(test PRIVATE Qt5::Widgets
    ${CMAKE_SOURCE_DIR}/libs/cef/lib/debug/libcef.lib
    ${CMAKE_SOURCE_DIR}/libs/cef/lib/debug/libcef_dll_wrapper.lib
)

set_target_properties(test PROPERTIES
    WIN32_EXECUTABLE TRUE
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/Release"
)

add_custom_command(TARGET test POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/libs/cef/bin/debug"
    "$<TARGET_FILE_DIR:test>"
)

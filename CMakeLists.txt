cmake_minimum_required(VERSION 3.16)

project(cef_widget VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

# 源码文件（src 目录下）
set(PROJECT_SOURCES
    src/main.cpp
    src/app.cpp
    src/app.h
    src/main_window.cpp
    src/main_window.h
    src/cef/QCefApp.cpp
    src/cef/QCefApp.h
    src/cef/QCefAppBrowser.cpp
    src/cef/QCefAppBrowser.h
    src/cef/QCefAppRender.cpp
    src/cef/QCefAppRender.h
    src/cef/QCefClient.cpp
    src/cef/QCefClient.h
    src/cef/QCefGlobalDefine.h
    src/cef/cef_query_handler.cpp
    src/cef/cef_query_handler.h
    src/cef/QCefWidget.cpp
    src/cef/QCefWidget.h
    src/log/log.cpp
    src/log/log.h
)

add_executable(cef_widget
    ${PROJECT_SOURCES}
)

# 头文件包含路径
target_include_directories(cef_widget PRIVATE
    ${CMAKE_SOURCE_DIR}/libs/cef
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(cef_widget PRIVATE Qt5::Widgets
    ${CMAKE_SOURCE_DIR}/libs/cef/lib/debug/libcef.lib
    ${CMAKE_SOURCE_DIR}/libs/cef/lib/debug/libcef_dll_wrapper.lib
)

set_target_properties(cef_widget PROPERTIES
    WIN32_EXECUTABLE TRUE
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/build/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/build/Release"
)

add_custom_command(TARGET cef_widget POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/libs/cef/bin/debug"
    "$<TARGET_FILE_DIR:cef_widget>"
)

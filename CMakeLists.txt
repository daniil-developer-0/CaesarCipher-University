cmake_minimum_required(VERSION 3.5)

project(CaesarWork VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(ANDROID)
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    if (ANDROID_ABI STREQUAL "armeabi-v7a")
        set(ANDROID_EXTRA_LIBS
            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
    endif()
endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        Caesar.cpp
        Caesar.h
        caesar.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CaesarWork
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(CaesarWork SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(CaesarWork
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(CaesarWork PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(CaesarWork PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CaesarWork)
endif()

cmake_minimum_required(VERSION 3.16)
project(file_searcher VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 COMPONENTS Widgets Concurrent REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Concurrent REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    filesearcher.cpp
)

set(PROJECT_HEADERS
    mainwindow.h
    filesearcher.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(file_searcher
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
    )
else()
    add_executable(file_searcher
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
    )
endif()

target_link_libraries(file_searcher PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Concurrent
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(file_searcher)
endif()

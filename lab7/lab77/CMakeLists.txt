cmake_minimum_required(VERSION 3.16)

project(laba77 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем основные модули Qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Quick Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Quick Sql)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui


)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(laba77
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        main.qml
    )

    # Добавляем QML модуль
    qt_add_qml_module(laba77
        URI Laba77
        VERSION 1.0
        QML_FILES main.qml
        QML_FILES
        QML_FILES
        SOURCES database.h database.cpp
    )
else()
    if(ANDROID)
        add_library(laba77 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(laba77
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Подключаем все необходимые модули
target_link_libraries(laba77 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Sql
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.laba77)
endif()
set_target_properties(laba77 PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS laba77
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(laba77)
endif()

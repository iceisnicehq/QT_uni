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
        SOURCES database.h database.cpp
    )
set(QXLSX_SOURCES
    QXlsx/source/xlsxzipwriter.cpp
    QXlsx/source/xlsxcontenttypes.cpp
    QXlsx/source/xlsxdrawinganchor.cpp
    QXlsx/source/xlsxcelllocation.cpp
    QXlsx/source/xlsxcellformula.cpp
    QXlsx/source/xlsxnumformatparser.cpp
    QXlsx/source/xlsxabstractooxmlfile.cpp
    QXlsx/source/xlsxsharedstrings.cpp
    QXlsx/source/xlsxchartsheet.cpp
    QXlsx/source/xlsxcolor.cpp
    QXlsx/source/xlsxabstractsheet.cpp
    QXlsx/source/xlsxdocpropsapp.cpp
    QXlsx/source/xlsxzipreader.cpp
    QXlsx/source/xlsxdocpropscore.cpp
    QXlsx/source/xlsxconditionalformatting.cpp
    QXlsx/source/xlsxstyles.cpp
    QXlsx/source/xlsxutility.cpp
    QXlsx/source/xlsxtheme.cpp
    QXlsx/source/xlsxdocument.cpp
    QXlsx/source/xlsxcell.cpp
    QXlsx/source/xlsxcellreference.cpp
    QXlsx/source/xlsxcellrange.cpp
    QXlsx/source/xlsxformat.cpp
    QXlsx/source/xlsxmediafile.cpp
    QXlsx/source/xlsxworksheet.cpp
    QXlsx/source/xlsxdatavalidation.cpp
    QXlsx/source/xlsxrichstring.cpp
    QXlsx/source/xlsxdrawing.cpp
    QXlsx/source/xlsxsimpleooxmlfile.cpp
    QXlsx/source/xlsxdatetype.cpp
    QXlsx/source/xlsxrelationships.cpp
    QXlsx/source/xlsxworkbook.cpp
    QXlsx/source/xlsxchart.cpp
)

set(QXLSX_HEADERS
    QXlsx/header/xlsxdocument.h
    QXlsx/header/xlsxzipwriter_p.h
    QXlsx/header/xlsxdatetype.h
    QXlsx/header/xlsxdocument_p.h
    QXlsx/header/xlsxcellformula.h
    QXlsx/header/xlsxchartsheet_p.h
    QXlsx/header/xlsxabstractsheet_p.h
    QXlsx/header/xlsxdrawinganchor_p.h
    QXlsx/header/xlsxcellreference.h
    QXlsx/header/xlsxworkbook_p.h
    QXlsx/header/xlsxconditionalformatting_p.h
    QXlsx/header/xlsxdocpropsapp_p.h
    QXlsx/header/xlsxchart.h
    QXlsx/header/xlsxrelationships_p.h
    QXlsx/header/xlsxnumformatparser_p.h
    QXlsx/header/xlsxabstractooxmlfile_p.h
    QXlsx/header/xlsxdatavalidation.h
    QXlsx/header/xlsxformat.h
    QXlsx/header/xlsxrichstring_p.h
    QXlsx/header/xlsxdocpropscore_p.h
    QXlsx/header/xlsxzipreader_p.h
    QXlsx/header/xlsxmediafile_p.h
    QXlsx/header/xlsxcelllocation.h
    QXlsx/header/xlsxformat_p.h
    QXlsx/header/xlsxcellformula_p.h
    QXlsx/header/xlsxworksheet_p.h
    QXlsx/header/xlsxcontenttypes_p.h
    QXlsx/header/xlsxcellrange.h
    QXlsx/header/xlsxcolor_p.h
    QXlsx/header/xlsxcell.h
    QXlsx/header/xlsxcell_p.h
    QXlsx/header/xlsxabstractooxmlfile.h
    QXlsx/header/xlsxdrawing_p.h
    QXlsx/header/xlsxsimpleooxmlfile_p.h
    QXlsx/header/xlsxstyles_p.h
    QXlsx/header/xlsxchartsheet.h
    QXlsx/header/xlsxchart_p.h
    QXlsx/header/xlsxworksheet.h
    QXlsx/header/xlsxworkbook.h
    QXlsx/header/xlsxdatavalidation_p.h
    QXlsx/header/xlsxabstractsheet.h
    QXlsx/header/xlsxsharedstrings_p.h
    QXlsx/header/xlsxdocument.h
    QXlsx/header/xlsxconditionalformatting.h
    QXlsx/header/xlsxrichstring.h
    QXlsx/header/xlsxutility_p.h
    QXlsx/header/xlsxtheme_p.h
    QXlsx/header/xlsxglobal.h
)

file(GLOB QXLSX_SOURCES
    QXlsx/source/xlsx*.cpp
)

file(GLOB QXLSX_HEADERS
    QXlsx/header/xlsx*.h
)

target_sources(laba77 PRIVATE
    ${QXLSX_SOURCES}
    QXlsx/header/xlsxdocument.h
)
target_include_directories(laba77 PRIVATE QXlsx/header)

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

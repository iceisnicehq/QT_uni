TARGET = ru.template.laba14

CONFIG += \
    auroraapp

PKGCONFIG += \

SOURCES += \
    src/main.cpp \
    src/systemservice.cpp

HEADERS += \
    src/systemservice.h

DISTFILES += \
    rpm/ru.template.laba14.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

QT += qml quick dbus

TRANSLATIONS += \
    translations/ru.template.laba14.ts \
    translations/ru.template.laba14-ru.ts \

TARGET = ru.template.laba16

CONFIG += \
    auroraapp

PKGCONFIG += \

SOURCES += \
    src/main.cpp \

HEADERS += \

DISTFILES += \
    qml/pages/WeatherFetcher.js \
    rpm/ru.template.laba16.spec

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.template.laba16.ts \
    translations/ru.template.laba16-ru.ts \

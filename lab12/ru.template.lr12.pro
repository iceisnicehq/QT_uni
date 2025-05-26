TARGET = ru.template.lr12

CONFIG += \
    auroraapp

PKGCONFIG += \

SOURCES += \
    src/main.cpp \

HEADERS += \

DISTFILES += \
    rpm/ru.template.lr12.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.template.lr12.ts \
    translations/ru.template.lr12-ru.ts \

RESOURCES += \
    qml/source.qrc

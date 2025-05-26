TARGET = ru.template.lr13

CONFIG += \
    auroraapp

PKGCONFIG += \

SOURCES += \
    src/main.cpp \

HEADERS += \

DISTFILES += \
    rpm/ru.template.lr13.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

CONFIG += auroraapp_i18n

TRANSLATIONS += \
    translations/ru.template.lr13.ts \
    translations/ru.template.lr13-ru.ts \

RESOURCES += \
    qml/sound.qrc
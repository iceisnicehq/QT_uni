# SPDX-FileCopyrightText: 2023 Open Mobile Platform LLC <edu@omp.ru>
# SPDX-License-Identifier: BSD-3-Clause

TARGET = ru.auroraos.Animations

CONFIG += \
    auroraapp \

SOURCES += \
    src/main.cpp \

DISTFILES += \
    rpm/$${TARGET}.spec \

AURORAAPP_ICONS = 86x86 108x108 128x128 172x172

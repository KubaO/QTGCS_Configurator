QT = widgets

TARGET = QTGCS_Configurator
TEMPLATE = app
DEFINES += \
    QT_DEPRECATED_WARNINGS \
    QT_DISABLE_DEPRECATED_BEFORE=0x060000 \
    QT_RESTRICTED_CAST_FROM_ASCII

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    configureproperty.cpp

HEADERS += \
    mainwindow.h \
    configureproperty.h

FORMS += \
    mainwindow.ui

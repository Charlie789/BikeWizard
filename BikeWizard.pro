QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    bikewizardapplication.cpp \
    dbconnector.cpp \
    main.cpp \
    mainwindow.cpp \
    modelhandler.cpp

HEADERS += \
    bikewizardapplication.h \
    customtypes.h \
    dbconnector.h \
    mainwindow.h \
    modelhandler.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    BikeWizard_pl_PL.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

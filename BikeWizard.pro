QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    backgroundcolordelegate.cpp \
    bikewizardapplication.cpp \
    dbconnector.cpp \
    main.cpp \
    mainwindow.cpp \
    modelhandler.cpp \
    offergenerator.cpp \
    propertycontainter.cpp \
    propertymanager.cpp

HEADERS += \
    backgroundcolordelegate.h \
    bikewizardapplication.h \
    customtypes.h \
    dbconnector.h \
    mainwindow.h \
    modelhandler.h \
    offergenerator.h \
    propertycontainter.h \
    propertymanager.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    BikeWizard_pl_PL.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

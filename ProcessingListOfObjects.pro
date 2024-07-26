QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += utf8

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Comparator.cpp \
    DateGroupingStrategy.cpp \
    DistanceGroupingStrategy.cpp \
    Group.cpp \
    GroupingStrategy.cpp \
    Groupview.cpp \
    NameGroupingStrategy.cpp \
    Object.cpp \
    Subgroup.cpp \
    TypeGroupingStrategy.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Comparator.h \
    DateGroupingStrategy.h \
    DistanceGroupingStrategy.h \
    Group.h \
    GroupingStrategy.h \
    Groupview.h \
    NameGroupingStrategy.h \
    Object.h \
    Subgroup.h \
    TypeGroupingStrategy.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Data.txt \
    ProcessingListOfObjects.pro.user

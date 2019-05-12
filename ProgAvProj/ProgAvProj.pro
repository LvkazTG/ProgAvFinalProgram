#-------------------------------------------------
#
# Project created by QtCreator 2019-03-31T14:42:04
#
#-------------------------------------------------

QT       += core gui
QT += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProgAvProj
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

SOURCES += \
        basesearch.cpp \
        connlist.cpp \
        formatop.cpp \
        jsonop.cpp \
        main.cpp \
        mapaobj.cpp \
        mappaint.cpp \
        mapvisual.cpp \
        pointconniter.cpp \
        pointobj.cpp \
        progavprinc.cpp \
        routeresultpaint.cpp \
        searchastart.cpp \
        searchdeep.cpp \
        searchgraphplanadapt.cpp \
        searchlevel.cpp \
        searchmanual.cpp \
        searchresultdlg.cpp \
        searchstatistics.cpp \
        searchuserstart.cpp \
        xmlop.cpp

HEADERS += \
        basesearch.h \
        connlist.h \
        formatop.h \
        jsonop.h \
        mapaobj.h \
        mappaint.h \
        mapvisual.h \
        pointconniter.h \
        pointobj.h \
        progavprinc.h \
        routeresultpaint.h \
        searchastart.h \
        searchdeep.h \
        searchgraphplanadapt.h \
        searchlevel.h \
        searchmanual.h \
        searchresultdlg.h \
        searchstatistics.h \
        searchuserstart.h \
        xmlop.h

FORMS += \
        mapvisual.ui \
        progavprinc.ui \
        searchmanual.ui \
        searchresultdlg.ui \
        searchuserstart.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

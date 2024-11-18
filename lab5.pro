#-------------------------------------------------
#
# Project created by QtCreator 2024-10-03T20:06:32
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab5
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

CONFIG += c++11

SOURCES += \
        circle.cpp \
        complexobject.cpp \
        customgraphicsview.cpp \
        edit_functions.cpp \
        file_funct.cpp \
        flower.cpp \
        graphics_editor.cpp \
        line.cpp \
        main.cpp \
        mainwindow.cpp \
        mart_letters.cpp \
        movabletextitem.cpp \
        park_letters.cpp \
        rectangle.cpp \
        shape.cpp \
        triangle.cpp \
        dog.cpp \
        var_letters.cpp

HEADERS += \
        circle.h \
        complexobject.h \
        customgraphicsview.h \
        edit_functions.h \
        file_funct.h \
        flower.h \
        graphics_editor.h \
        line.h \
        mainwindow.h \
        martword.h \
        movabletextitem.h \
        parkword.h \
        rectangle.h \
        shape.h \
        triangle.h \
        dog.h \
        varword.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icons/toolbar/allChars.bmp \
    icons/toolbar/closeAll.bmp \
    icons/toolbar/closeFile.bmp \
    icons/toolbar/copy.bmp \
    icons/toolbar/cut.bmp \
    icons/toolbar/docList.bmp \
    icons/toolbar/docMap.bmp \
    icons/toolbar/fileBrowser.bmp \
    icons/toolbar/find.bmp \
    icons/toolbar/findReplace.bmp \
    icons/toolbar/funcList.bmp \
    icons/toolbar/indentGuide.bmp \
    icons/toolbar/monitoring.bmp \
    icons/toolbar/newFile.bmp \
    icons/toolbar/openFile.bmp \
    icons/toolbar/paste.bmp \
    icons/toolbar/playRecord.bmp \
    icons/toolbar/playRecord_m.bmp \
    icons/toolbar/print.bmp \
    icons/toolbar/redo.bmp \
    icons/toolbar/saveAll.bmp \
    icons/toolbar/saveFile.bmp \
    icons/toolbar/saveRecord.bmp \
    icons/toolbar/startRecord.bmp \
    icons/toolbar/stopRecord.bmp \
    icons/toolbar/syncH.bmp \
    icons/toolbar/syncV.bmp \
    icons/toolbar/udl.bmp \
    icons/toolbar/undo.bmp \
    icons/toolbar/wrap.bmp \
    icons/toolbar/zoomIn.bmp \
    icons/toolbar/zoomOut.bmp \
    sounds/coliz.mp3 \
    sounds/collision.mp3

RESOURCES += \
    icons/toolbar/toolbar.qrc



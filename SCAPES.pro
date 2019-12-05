#-------------------------------------------------
#
# Project created by QtCreator 2019-10-27T21:27:13
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SCAPES
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
        control/src/compileControl.cpp \
        control/src/errorControl.cpp \
        control/src/runControl.cpp \
        control/src/saveControl.cpp \
        entity/src/identifier.cpp \
        entity/src/jsonHandler.cpp \
        entity/src/label.cpp \
        entity/src/operand.cpp \
        entity/src/program.cpp \
        entity/src/statement.cpp \
        entity/src/variable.cpp \
        entity/stmts/src/addStmt.cpp \
        entity/stmts/src/compStmt.cpp \
        entity/stmts/src/declArrStmt.cpp \
        entity/stmts/src/declIntStmt.cpp \
        entity/stmts/src/endStmt.cpp \
        entity/stmts/src/jEqStmt.cpp \
        entity/stmts/src/jLessStmt.cpp \
        entity/stmts/src/jMoreStmt.cpp \
        entity/stmts/src/jumpStmt.cpp \
        entity/stmts/src/movStmt.cpp \
        entity/stmts/src/printStmt.cpp \
        entity/stmts/src/readStmt.cpp \
        interface/src/highlighter.cpp \
        interface/src/inputwindow.cpp \
        interface/src/main.cpp \
        interface/src/mainwindow.cpp \
        interface/src/opennewwidget.cpp \
        interface/src/outputtabwidget.cpp \
        interface/src/tabchildwidget.cpp

HEADERS += \
        control/inc/compileControl.h \
        control/inc/errorControl.h \
        control/inc/runControl.h \
        control/inc/saveControl.h \
        entity/inc/common_lib.h \
        entity/inc/identifier.h \
        entity/inc/jsonHandler.h \
        entity/inc/label.h \
        entity/inc/operand.h \
        entity/inc/program.h \
        entity/inc/statement.h \
        entity/inc/variable.h \
        entity/stmts/inc/addStmt.h \
        entity/stmts/inc/compStmt.h \
        entity/stmts/inc/declArrStmt.h \
        entity/stmts/inc/declIntStmt.h \
        entity/stmts/inc/endStmt.h \
        entity/stmts/inc/jEqStmt.h \
        entity/stmts/inc/jLessStmt.h \
        entity/stmts/inc/jMoreStmt.h \
        entity/stmts/inc/jumpStmt.h \
        entity/stmts/inc/movStmt.h \
        entity/stmts/inc/printStmt.h \
        entity/stmts/inc/readStmt.h \
        interface/inc/highlighter.h \
        interface/inc/inputwindow.h \
        interface/inc/mainwindow.h \
        interface/inc/opennewwidget.h \
        interface/inc/outputtabwidget.h \
        interface/inc/tabchildwidget.h

FORMS += \
        interface/ui/inputwindow.ui \
        interface/ui/mainwindow.ui \
        interface/ui/opennewwidget.ui \
        interface/ui/outputtabwidget.ui \
        interface/ui/tabchildwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    interface/res/res.qrc

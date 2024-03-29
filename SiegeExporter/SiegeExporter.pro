QT       += core gui testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11 console staticllib

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_STATIC_BUILD

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    format/Header.cpp \
    format/Serializable.cpp \
    format/String.cpp \
    format/UnicodeString.cpp \
    main.cpp \
    MainWindow.cpp \
    System.cpp \
    format/S2M.cpp

HEADERS += \
    MainWindow.h \
    format/Header.h \
    format/HeaderOption.h \
    format/List.h \
    format/List.tpp \
    format/Serializable.h \
    format/String.h \
    format/UnicodeString.h \
    System.h \
    format/S2M.h \
    format/Compressed.h \
    format/Compressed.tpp \
    tests/TestCompressed.h

FORMS += \
    MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

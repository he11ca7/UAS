greaterThan(QT_MAJOR_VERSION, 4) {
    QT += printsupport
    QT += concurrent
    QT += widgets
}

QT += \
    core \
    gui \
    svg \
    xml

TEMPLATE = app
INCLUDEPATH += \
    ../lib_UAS/headers \
    ../lib_customClasses/headers \
    headers

SOURCES += \
    sources/main.cpp \
    sources/clsMainWindow.cpp

HEADERS += \
    headers/clsMainWindow.h

DESTDIR += ../EXE
QMAKE_LIBDIR += ../LIB

CONFIG(debug, debug|release) {
    LIBS    += \
            -lUASd \
            -lcustomClassesd
    TARGET  = main_d
} else {
    LIBS    += \
            -lUAS \
            -lcustomClasses
    TARGET  = main
}

RESOURCES += \
    resources/main_res.qrc

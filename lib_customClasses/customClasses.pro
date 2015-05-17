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

TEMPLATE = lib
CONFIG += staticlib
OBJECTS_DIR = obj
MOC_DIR = moc

INCLUDEPATH += \
    headers

QMAKE_LIBDIR += ../LIB
DESTDIR      = ../LIB

SOURCES += \
    sources/clsMessageBox.cpp \
    sources/clsVisibilityButton.cpp \
    sources/clsPasswordLineEdit.cpp \
    sources/clsGridScrollAreaWidget.cpp

HEADERS += \
    headers/nspCustomClasses.h

CONFIG(debug, debug|release) {
    TARGET  = customClassesd
} else {
    TARGET  = customClasses
}

RESOURCES += \
    resources/customClasses_res.qrc

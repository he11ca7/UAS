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
    ../lib_customClasses/headers \
    headers

QMAKE_LIBDIR += ../LIB
DESTDIR      = ../LIB

SOURCES += \
    sources/clsLoginEngine.cpp \
    sources/clsGroup.cpp \
    sources/clsGroupsEngine.cpp \
    sources/clsLoginDialog.cpp \
    sources/clsUser.cpp \
    sources/clsUsersEngine.cpp \
    sources/clsPasswordChangeDialog.cpp \
    sources/clsPasswordSetDialog.cpp \
    sources/clsUserWidget.cpp \
    sources/clsUsersWidget.cpp \
    sources/clsUserSettingsButton.cpp \
    sources/clsAddUserDialog.cpp \
    sources/clsUserSettingsDialog.cpp \
    sources/dataStream.cpp

HEADERS += \
    headers/nspCore.h \
    headers/nspGUI.h \
    headers/nspUAS.h

CONFIG(debug, debug|release) {
    TARGET  = UASd
    LIBS    += \
            -lcustomClassesd
} else {
    TARGET  = UAS
    LIBS    += \
            -lcustomClasses
}

RESOURCES += \
    resources/UAS_res.qrc

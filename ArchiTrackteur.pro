TEMPLATE = app

CONFIG += c++11

QT += qml quick widgets

SOURCES += src/main.cpp \
    src/controller/controller.cpp \
    src/model/archilist.cpp \
    src/model/archilistproxy.cpp \
    src/io/savefilemanager.cpp \
    src/model/archistats.cpp

RESOURCES += view/qml.qrc

OTHER_FILES += data/archidata.json

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/controller/controller.h \
    src/model/archilist.h \
    src/model/archilistproxy.h \
    src/io/savefilemanager.h \
    src/model/archistats.h


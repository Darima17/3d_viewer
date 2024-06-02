QT       += core gui opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 5): QT += openglwidgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    momento.cc \
    glViewer.cc \
    mainwindow.cc \
    ../models/figure.cc \
    ../models/edges.cc \
    ../models/faces.cc \
    ../models/point.cc \
    ../models/points.cc \
    main.cc \
    gifUtils/dgif_lib.cpp \
    gifUtils/egif_lib.cpp \
    gifUtils/gif_err.cpp \
    gifUtils/gif_font.cpp \
    gifUtils/gif_hash.cpp \
    gifUtils/gifalloc.cpp \
    gifUtils/qgifimage.cpp \
    gifUtils/quantize.cpp
HEADERS += \
    momento.h \
    glViewer.h \
    mainwindow.h \
    ../models/figure.h \
    ../models/edges.h \
    ../models/faces.h \
    ../models/point.h \
    ../models/points.h \
    gifUtils/gif_hash.h \
    gifUtils/gif_lib.h \
    gifUtils/gif_lib_private.h \
    gifUtils/qgifglobal.h \
    gifUtils/qgifimage.h \
    gifUtils/qgifimage_p.h


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui

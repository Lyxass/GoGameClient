QT += core gui
QT += widgets
QMAKE_CXXFLAGS += "-fno-sized-deallocation"
SOURCES += \
    golabel.cpp \
    gopassbutton.cpp \
    gopawn.cpp \
    ipwindow.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    golabel.h \
    gopassbutton.h \
    gopawn.h \
    ipwindow.h \
    mainwindow.h

DISTFILES += \
    Goban_9x9_.png \
    blanc.png \
    noir.png

RESOURCES += \
    Goban.qrc

# QGlobalShortcut
Crossplatform Global HotKey for Qt5.1 and higher

# Configuration of PRO File
```
CONFIG += c++11

linux {
    QT       += x11extras
    CONFIG   += link_pkgconfig
    PKGCONFIG += x11
}

win32: SOURCES += win/qglobalshortcut.cpp
linux: SOURCES += x11/qglobalshortcut.cpp

HEADERS  += qglobalshortcut.h
```

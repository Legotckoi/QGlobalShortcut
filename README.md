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

SOURCES += qglobalshortcut.cpp
win32: SOURCES += win/qglobalshortcut_p.cpp

HEADERS  += qglobalshortcut.h
win32: HEADERS += win/qglobalshortcut_p.h
```

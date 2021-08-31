# QGlobalShortcut
Crossplatform Global HotKey for Qt5.1 and higher

# Configuration of PRO File
You have to download library to specials folder in your project.
For example, name of folder is "QGlobalShortcut".
And include this .pri project in your .pro file.
```
include(QGlobalShortcut/qglobalshortcut.pri)
```

# Configuration of CMakeLists.txt
You have to download library to specials folder in your project.
For example, name of folder is "QGlobalShortcut".
And include this directory in your CMakeLists.txt file and link library to your target.
```
add_subdirectory(QGlobalShortcut)
...
target_link_libraries(<target> PRIVATE QGlobalShortcut)
add_dependencies(<target> qglobalshortcut)
```

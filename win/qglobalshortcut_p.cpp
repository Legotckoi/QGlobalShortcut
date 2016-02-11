#include "qglobalshortcut_p.h"
#include <QStringList>
#include <QKeySequence>
#include <QDebug>
#include "windows.h"

namespace
{
    static HWND firstWindowCreatedId = NULL;

    unsigned int winKeyModificator(const QKeySequence &sequence)
    {
        QStringList list = sequence.toString().split("+");
        unsigned int keyModificator = 0;

        foreach (QString str, list) {
            if(str == "Ctrl"){
                keyModificator |= MOD_CONTROL;
                continue;
            } else if(str == "Alt"){
                keyModificator |= MOD_ALT;
                continue;
            } else if(str == "Shift"){
                keyModificator |= MOD_SHIFT;
                continue;
            } else if(str == "Meta"){
                keyModificator |= MOD_WIN;
                continue;
            }
        }
        return keyModificator;
    }

    unsigned int winHotKey(const QKeySequence &sequence)
    {
        QStringList list = sequence.toString().split("+");
        unsigned int key = 0;
        foreach (QString str, list) {
            if(str != "Ctrl" && str != "Alt" && str != "Shift"){
                key = str.at(0).unicode();
            }
        }
        return key;
    }
}

QGlobalShortcutPrivate::QGlobalShortcutPrivate(QObject *parent) : QObject(parent)
{
    key = 0;
    modifiers = 0;
    id = 0;
}

bool QGlobalShortcutPrivate::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)
    MSG* msg = reinterpret_cast<MSG*>(message);
    if (firstWindowCreatedId == NULL)
        firstWindowCreatedId = msg->hwnd;
    if(msg->message == WM_HOTKEY){

        if(msg->wParam == id){
            emit activated();
            return true;
        }
    }
    return false;
}

bool QGlobalShortcutPrivate::registerKeySequence(const QKeySequence &keySequence)
{
    if(key != 0 || modifiers != 0 || id != 0){
        UnregisterHotKey(firstWindowCreatedId, id);
    }
    key = winHotKey(keySequence);
    modifiers = winKeyModificator(keySequence);
    id = key ^ modifiers;
    return RegisterHotKey(firstWindowCreatedId, id, modifiers, key);
}

bool QGlobalShortcutPrivate::unRegisterKeySequence()
{
    return UnregisterHotKey(firstWindowCreatedId, id);
}


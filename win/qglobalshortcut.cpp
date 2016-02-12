#include "qglobalshortcut.h"
#include <QStringList>
#include <QDebug>
#include "windows.h"

namespace
{
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
        QString str = list.last();
        if(str.length() == 0){
            return VK_ADD;              // return "+"
        } else if(str.length() == 1){
            return str.at(0).unicode(); // return Key Letters and Numbers
        } else {
            if(str == "Esc"){
                return VK_ESCAPE;
            } else if(str == "Tab" || str == "BackTab"){
                return VK_TAB;
            } else if(str == "Backspace"){
                return VK_BACK;
            } else if(str == "Return" || str == "Enter"){
                return VK_RETURN;
            } else if(str == "Ins"){
                return VK_INSERT;
            } else if(str == "Del"){
                return VK_DELETE;
            } else if(str == "Pause"){
                return VK_PAUSE;
            } else if(str == "Print"){
                return VK_PRINT;
            } else if(str == "SysReq"){
                return VK_SNAPSHOT;
            } else if(str == "Clear"){
                return VK_CLEAR;
            } else if(str == "Home"){
                return VK_HOME;
            } else if(str == "End"){
                return VK_END;
            } else if(str == "Left"){
                return VK_LEFT;
            } else if(str == "Up"){
                return VK_UP;
            } else if(str == "Right"){
                return VK_RIGHT;
            } else if(str == "Down"){
                return VK_DOWN;
            } else if(str == "PgUp"){
                return VK_PRIOR;
            } else if(str == "PgDown"){
                return VK_NEXT;
            } else if(str == "F1"){
                return VK_F1;
            } else if(str == "F2"){
                return VK_F2;
            } else if(str == "3"){
                return VK_F3;
            } else if(str == "F4"){
                return VK_F4;
            } else if(str == "F5"){
                return VK_F5;
            } else if(str == "F6"){
                return VK_F6;
            } else if(str == "F7"){
                return VK_F7;
            } else if(str == "F8"){
                return VK_F8;
            } else if(str == "F9"){
                return VK_F9;
            } else if(str == "F10"){
                return VK_F10;
            } else if(str == "F11"){
                return VK_F11;
            } else if(str == "F12"){
                return VK_F12;
            } else if(str == "F13"){
                return VK_F13;
            } else if(str == "F14"){
                return VK_F14;
            } else if(str == "F15"){
                return VK_F15;
            } else if(str == "F16"){
                return VK_F16;
            } else if(str == "F17"){
                return VK_F17;
            } else if(str == "F18"){
                return VK_F18;
            } else if(str == "F19"){
                return VK_F19;
            } else if(str == "F20"){
                return VK_F20;
            } else if(str == "F21"){
                return VK_F21;
            } else if(str == "F22"){
                return VK_F22;
            } else if(str == "F23"){
                return VK_F23;
            } else if(str == "F24"){
                return VK_F24;
            } else if(str == "Space"){
                return VK_SPACE;
            } else if(str == "*"){
                return VK_MULTIPLY;
            } else if(str == ","){
                return VK_SEPARATOR;
            } else if(str == "-"){
                return VK_SUBTRACT;
            } else if(str == "/"){
                return VK_DIVIDE;
            } else if(str == "Media Next"){
                return VK_MEDIA_NEXT_TRACK;
            } else if(str == "Media Previous"){
                return VK_MEDIA_PREV_TRACK;
            } else if(str == "Media Play"){
                return VK_MEDIA_PLAY_PAUSE;
            } else if(str == "Media Stop"){
                return VK_MEDIA_STOP;
            } else if(str == "Volume Down"){
                return VK_VOLUME_DOWN;
            } else if(str == "Volume Up"){
                return VK_VOLUME_UP;
            } else if(str == "Volume Mute"){
                return VK_VOLUME_MUTE;
            } else {
                return 0;
            }
        }
    }

    unsigned int winId(const QKeySequence &keySequence)
    {
        return winHotKey(keySequence) ^ winKeyModificator(keySequence);
    }
}

class QGlobalData
{
    Q_PROPERTY(unsigned int id READ id WRITE setId)

public:
    QGlobalData() {}

    QGlobalData(const QGlobalData &other) :
        m_id(other.m_id)
    {

    }

    unsigned int id(){return m_id;}
    void setId(unsigned int id){m_id = id;}

private:
    unsigned int m_id;
};

class QGlobalShortcutPrivate
{
public:
    QKeySequence keys;
    QList<QGlobalData*>listKeys;

    QGlobalShortcutPrivate() {

    }
};

QGlobalShortcut::QGlobalShortcut(QObject *parent) :
    QObject(parent),
    sPrivate(new QGlobalShortcutPrivate)
{
    qApp->installNativeEventFilter(this);
}

QGlobalShortcut::~QGlobalShortcut()
{
    qApp->removeNativeEventFilter(this);
    unsetShortcut();
    delete sPrivate;
}

bool QGlobalShortcut::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)
    if(!sPrivate->keys.isEmpty()){
        MSG* msg = reinterpret_cast<MSG*>(message);
        if(msg->message == WM_HOTKEY){
            foreach (QGlobalData *data, sPrivate->listKeys) {
                if(msg->wParam == data->id()){
                    emit activated();
                    return true;
                }
            }
        }
    }
    return false;
}

bool QGlobalShortcut::setShortcut(const QKeySequence &keySequence)
{
    if(!sPrivate->keys.isEmpty())unsetShortcut();
    sPrivate->keys = keySequence;
    QStringList list = sPrivate->keys.toString().split(", ");
    foreach (QString str, list) {
        QGlobalData * data = new QGlobalData();
        data->setId(winId(QKeySequence(str)));
        sPrivate->listKeys.append(data);
        RegisterHotKey(0, data->id(), winKeyModificator(QKeySequence(str)), winHotKey(QKeySequence(str)));
    }
    return true;
}

bool QGlobalShortcut::unsetShortcut()
{
    if(!sPrivate->keys.isEmpty()){
        foreach (QGlobalData *data, sPrivate->listKeys) {
            UnregisterHotKey(0, data->id());
        }
        sPrivate->listKeys.clear();
    }
    return true;
}


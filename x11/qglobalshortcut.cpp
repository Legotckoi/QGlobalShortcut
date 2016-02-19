#include "qglobalshortcut.h"
#include <QApplication>
#include <QStringList>
#include <QKeySequence>
#include <QVector>
#include <QX11Info>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <xcb/xcb.h>

namespace
{
    Display * m_display;
    Window m_win;

    QVector<quint32> maskModifiers(){
        return QVector<quint32>() << 0 << Mod2Mask << LockMask << (Mod2Mask | LockMask);
    }

    unsigned int X11KeyModificator(const QKeySequence &sequence)
    {
        QStringList list = sequence.toString().split("+");
        unsigned int keyModificator = 0;

        foreach (QString str, list) {
            if(str == "Ctrl"){
                keyModificator |= XCB_MOD_MASK_CONTROL;
                continue;
            } else if(str == "Alt"){
                keyModificator |= XCB_MOD_MASK_1;
                continue;
            } else if(str == "Shift"){
                keyModificator |= XCB_MOD_MASK_SHIFT;
                continue;
            } else if(str == "Meta"){
                keyModificator |= XCB_MOD_MASK_4;
                continue;
            }
        }
        return keyModificator;
    }

    unsigned int X11HotKey(Display *display, const QKeySequence &sequence)
    {
        QStringList list = sequence.toString().split("+");
        QString str = list.last();
        if(str.length() == 0){
            return XKeysymToKeycode(display, XK_plus);             // return "+"
        } else if(str.length() == 1){
            return XKeysymToKeycode(display, str.at(0).unicode()); // return Key Letters and Numbers
        } else {
            if(str == "Esc"){
                return XKeysymToKeycode(display, XK_Escape);
            } else if(str == "Tab" || str == "BackTab"){
                return XKeysymToKeycode(display, XK_Tab);
            } else if(str == "Backspace"){
                return XKeysymToKeycode(display, XK_BackSpace);
            } else if(str == "Return" || str == "Enter"){
                return XKeysymToKeycode(display, XK_Return);
            } else if(str == "Ins"){
                return XKeysymToKeycode(display, XK_Insert);
            } else if(str == "Del"){
                return XKeysymToKeycode(display, XK_Delete);
            } else if(str == "Pause"){
                return XKeysymToKeycode(display, XK_Pause);
            } else if(str == "Print"){
                return XKeysymToKeycode(display, XK_Print);
            } else if(str == "SysReq"){
                return XKeysymToKeycode(display, XK_Sys_Req);
            } else if(str == "Clear"){
                return XKeysymToKeycode(display, XK_Clear);
            } else if(str == "Home"){
                return XKeysymToKeycode(display, XK_Home);
            } else if(str == "End"){
                return XKeysymToKeycode(display, XK_End);
            } else if(str == "Left"){
                return XKeysymToKeycode(display, XK_Left);
            } else if(str == "Up"){
                return XKeysymToKeycode(display, XK_Up);
            } else if(str == "Right"){
                return XKeysymToKeycode(display, XK_Right);
            } else if(str == "Down"){
                return XKeysymToKeycode(display, XK_Down);
            } else if(str == "PgUp"){
                return XKeysymToKeycode(display, XK_Page_Up);
            } else if(str == "PgDown"){
                return XKeysymToKeycode(display, XK_Page_Down);
            } else if(str == "F1"){
                return XKeysymToKeycode(display, XK_F1);
            } else if(str == "F2"){
                return XKeysymToKeycode(display, XK_F2);
            } else if(str == "3"){
                return XKeysymToKeycode(display, XK_F3);
            } else if(str == "F4"){
                return XKeysymToKeycode(display, XK_F4);
            } else if(str == "F5"){
                return XKeysymToKeycode(display, XK_F5);
            } else if(str == "F6"){
                return XKeysymToKeycode(display, XK_F6);
            } else if(str == "F7"){
                return XKeysymToKeycode(display, XK_F7);
            } else if(str == "F8"){
                return XKeysymToKeycode(display, XK_F8);
            } else if(str == "F9"){
                return XKeysymToKeycode(display, XK_F9);
            } else if(str == "F10"){
                return XKeysymToKeycode(display, XK_F10);
            } else if(str == "F11"){
                return XKeysymToKeycode(display, XK_F11);
            } else if(str == "F12"){
                return XKeysymToKeycode(display, XK_F12);
            } else if(str == "F13"){
                return XKeysymToKeycode(display, XK_F13);
            } else if(str == "F14"){
                return XKeysymToKeycode(display, XK_F14);
            } else if(str == "F15"){
                return XKeysymToKeycode(display, XK_F15);
            } else if(str == "F16"){
                return XKeysymToKeycode(display, XK_F16);
            } else if(str == "F17"){
                return XKeysymToKeycode(display, XK_F17);
            } else if(str == "F18"){
                return XKeysymToKeycode(display, XK_F18);
            } else if(str == "F19"){
                return XKeysymToKeycode(display, XK_F19);
            } else if(str == "F20"){
                return XKeysymToKeycode(display, XK_F20);
            } else if(str == "F21"){
                return XKeysymToKeycode(display, XK_F21);
            } else if(str == "F22"){
                return XKeysymToKeycode(display, XK_F22);
            } else if(str == "F23"){
                return XKeysymToKeycode(display, XK_F23);
            } else if(str == "F24"){
                return XKeysymToKeycode(display, XK_F24);
            } else if(str == "Space"){
                return XKeysymToKeycode(display, XK_space);
            } else if(str == "*"){
                return XKeysymToKeycode(display, XK_asterisk);
            } else if(str == ","){
                return XKeysymToKeycode(display, XK_comma);
            } else if(str == "-"){
                return XKeysymToKeycode(display, XK_minus);
            } else if(str == "/"){
                return XKeysymToKeycode(display, XK_slash);
            } else {
                return 0;
            }
        }
    }
}

class QGlobalData
{
    Q_PROPERTY(unsigned int key READ key WRITE setKey)
    Q_PROPERTY(unsigned int modifier READ modifier WRITE setModifier)

public:
    QGlobalData() {}

    QGlobalData(const QGlobalData &other) :
        m_key(other.m_key),
        m_modifier(other.m_modifier)
    {

    }

    unsigned int key(){return m_key;}
    unsigned int modifier(){return m_modifier;}
    void setkey(unsigned int key){m_key = key;}
    void setModifier(unsigned int modifier){m_modifier = modifier;}

private:
    unsigned int m_key;
    unsigned int m_modifier;
};

class QGlobalShortcutPrivate
{
public:
    QKeySequence keys;
    QList<QGlobalData*>listKeys;
    bool enabled;

    QGlobalShortcutPrivate() {

    }
};

QGlobalShortcut::QGlobalShortcut(QObject *parent) :
    QObject(parent),
    sPrivate(new QGlobalShortcutPrivate)
{
    m_display = QX11Info::display();
    m_win = DefaultRootWindow(m_display);
    sPrivate->enabled = true;
    qApp->installNativeEventFilter(this);
}

QGlobalShortcut::~QGlobalShortcut()
{
    unsetShortcut();
    qApp->removeNativeEventFilter(this);
    delete sPrivate;
}

bool QGlobalShortcut::nativeEventFilter(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)
    Q_UNUSED(result)

    if(!sPrivate->keys.isEmpty() && sPrivate->enabled){
        xcb_key_press_event_t *keyEvent = 0;
        if (eventType == "xcb_generic_event_t") {
            xcb_generic_event_t *event = static_cast<xcb_generic_event_t *>(message);
            if ((event->response_type & 127) == XCB_KEY_PRESS){
                keyEvent = static_cast<xcb_key_press_event_t *>(message);
                foreach (QGlobalData *data, sPrivate->listKeys) {
                    foreach (quint32 maskMods, maskModifiers()) {
                        if((keyEvent->state == (data->modifier() | maskMods ))
                                &&  keyEvent->detail == data->key()){
                            emit activated();
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool QGlobalShortcut::setShortcut(const QKeySequence &keySequence)
{
    unsetShortcut();
    sPrivate->keys = keySequence;
    QStringList list = sPrivate->keys.toString().split(", ");
    foreach (QString str, list) {
        QGlobalData * data = new QGlobalData();
        data->setkey(X11HotKey(m_display, QKeySequence(str)));
        data->setModifier(X11KeyModificator(QKeySequence(str)));
        sPrivate->listKeys.append(data);
        foreach (quint32 maskMods, maskModifiers()) {
            XGrabKey(m_display, data->key() , data->modifier() | maskMods, m_win,True, GrabModeAsync, GrabModeAsync);
        }
    }
    return true;
}

bool QGlobalShortcut::unsetShortcut()
{
    if(!sPrivate->keys.isEmpty()){
        foreach (QGlobalData *data, sPrivate->listKeys) {
            foreach (quint32 maskMods, maskModifiers()) {
                XUngrabKey(m_display, data->key(),data->modifier() | maskMods, m_win);
            }
        }
        sPrivate->listKeys.clear();
    }
    return true;
}

QKeySequence QGlobalShortcut::shortcut()
{
    if(!sPrivate->keys.isEmpty()){
        return sPrivate->keys;
    } else {
        return QKeySequence("");
    }
}

bool QGlobalShortcut::isEmpty()
{
    return sPrivate->keys.isEmpty();
}

void QGlobalShortcut::setEnabled(bool enable)
{
    sPrivate->enabled = enable;
}

bool QGlobalShortcut::isEnabled()
{
    return sPrivate->enabled;
}

#include "qglobalshortcut.h"
#include "qglobalshortcut_p.h"

QGlobalShortcut::QGlobalShortcut(QObject *parent) :
    QObject(parent),
    qGSPrivate(new QGlobalShortcutPrivate(parent))
{
    qApp->installNativeEventFilter(qGSPrivate);
    connect(qGSPrivate, &QGlobalShortcutPrivate::activated, this, &QGlobalShortcut::activated);
}

QGlobalShortcut::~QGlobalShortcut()
{
    delete qGSPrivate;
}

void QGlobalShortcut::setShortcut(const QKeySequence &keySequence)
{
    qGSPrivate->registerKeySequence(keySequence);
}

void QGlobalShortcut::unsetShortcut()
{
    qGSPrivate->unRegisterKeySequence();
}


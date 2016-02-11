#ifndef QGLOBALSHORTCUTPRIVATE_H
#define QGLOBALSHORTCUTPRIVATE_H

#include <QObject>
#include <QApplication>
#include <QAbstractNativeEventFilter>

class QKeySequence;

class QGlobalShortcutPrivate : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit QGlobalShortcutPrivate(QObject *parent = nullptr);

    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

    bool registerKeySequence(const QKeySequence &keySequence);
    bool unRegisterKeySequence();

signals:
    void activated();

public slots:

private:
   unsigned int key;
   unsigned int modifiers;
   unsigned int id;
};

#endif // QGLOBALSHORTCUTPRIVATE_H

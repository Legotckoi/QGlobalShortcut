#ifndef QGLOBALSHORTCUTPRIVATE_H
#define QGLOBALSHORTCUTPRIVATE_H

#include <QObject>
#include <QApplication>
#include <QAbstractNativeEventFilter>
#include <QKeySequence>

class QGlobalShortcut : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    explicit QGlobalShortcut(QObject *parent = nullptr);

    bool nativeEventFilter(const QByteArray &eventType, void *message, long *result) override;

    bool setShortcut(const QKeySequence &keySequence);
    bool unsetShortcut();

signals:
    void activated();

public slots:

private:
   QKeySequence keys;
};

#endif // QGLOBALSHORTCUTPRIVATE_H

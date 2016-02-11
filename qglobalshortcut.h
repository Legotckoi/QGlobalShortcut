#ifndef QGLOBALSHORTCUT_H
#define QGLOBALSHORTCUT_H

#include <QObject>

class QKeySequence;
class QGlobalShortcutPrivate;

class QGlobalShortcut : public QObject
{
    Q_OBJECT
public:
    explicit QGlobalShortcut(QObject *parent = 0);
    ~QGlobalShortcut();

    void setShortcut(const QKeySequence &keySequence);
    void unsetShortcut();

signals:
    void activated();

public slots:

private:
    QGlobalShortcutPrivate *qGSPrivate;
};

#endif // QGLOBALSHORTCUT_H

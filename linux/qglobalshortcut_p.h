#ifndef QGLOBALSHORTCUTPRIVATE_H
#define QGLOBALSHORTCUTPRIVATE_H

#include <QObject>

class QGlobalShortcutPrivate : public QObject
{
    Q_OBJECT
public:
    explicit QGlobalShortcutPrivate(QObject *parent = 0);

signals:

public slots:
};

#endif // QGLOBALSHORTCUTPRIVATE_H

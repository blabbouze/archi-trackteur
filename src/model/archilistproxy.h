#ifndef ARCHILISTPROXY_H
#define ARCHILISTPROXY_H

#include <QObject>
#include <qsortfilterproxymodel.h>

class ArchiListProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ArchiListProxy(QObject *parent = 0);
};

#endif // ARCHILISTPROXY_H

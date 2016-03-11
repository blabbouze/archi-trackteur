#ifndef ARCHILISTPROXY_H
#define ARCHILISTPROXY_H

#include <QObject>
#include <qsortfilterproxymodel.h>

class ArchiListProxy : public QSortFilterProxyModel
{
    Q_OBJECT

public:
    explicit ArchiListProxy(QObject *parent = 0);

public slots:
    void searchArchiByName(const QString& name);

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;

 private:
    QString name_wanted_;
};

#endif // ARCHILISTPROXY_H

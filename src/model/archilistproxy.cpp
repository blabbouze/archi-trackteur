#include "archilistproxy.h"
#include "archilist.h"

ArchiListProxy::ArchiListProxy(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

void ArchiListProxy::searchArchiByName(const QString &name)
{
     name_wanted_ = name;
     invalidateFilter();
}

bool ArchiListProxy::filterAcceptsRow(int sourceRow, const QModelIndex& /*sourceParent*/) const
{
    QModelIndex current_index = sourceModel()->index(sourceRow,0);

    QString archiName = sourceModel()->data(current_index,ArchiList::ArchiListRoles::ArchiNameRole).toString();
    QString monsterName = sourceModel()->data(current_index,ArchiList::ArchiListRoles::MonsterNameRole).toString();
    return (archiName.contains(name_wanted_,Qt::CaseInsensitive) || monsterName.contains(name_wanted_,Qt::CaseInsensitive));
}

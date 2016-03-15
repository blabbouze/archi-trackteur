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

void ArchiListProxy::showCapturedOnly()
{
    filter_captured_ = true;
    invalidateFilter();
}

void ArchiListProxy::showNotCapturedOnly()
{
    filter_not_captured_ = true;
    invalidateFilter();
}

void ArchiListProxy::resetCapturedFilters()
{
    filter_captured_ = false;
    filter_not_captured_ = false;
    invalidateFilter();
}

void ArchiListProxy::sortByStepProgress()
{
    this->sort(0,Qt::SortOrder::DescendingOrder);

}

void ArchiListProxy::resetSortFilters()
{
    this->sort(1);
}

bool ArchiListProxy::filterAcceptsRow(int sourceRow, const QModelIndex& /*sourceParent*/) const
{
    QModelIndex current_index = sourceModel()->index(sourceRow,0);

    QString archiName = sourceModel()->data(current_index,
                                            ArchiList::ArchiListRoles::ArchiNameRole).toString();
    QString monsterName = sourceModel()->data(current_index,
                                              ArchiList::ArchiListRoles::MonsterNameRole).toString();
    bool captured = sourceModel()->data(current_index,
                                    ArchiList::ArchiListRoles::CapturedRole).toBool();


    bool result = true;

    if (!name_wanted_.isEmpty()) {
        result = result && (archiName.contains(name_wanted_,Qt::CaseInsensitive) || monsterName.contains(name_wanted_,Qt::CaseInsensitive));
    }

    if (filter_captured_) {
        result = result && captured;
    }

    if (filter_not_captured_) {
        result = result && !captured;
    }
    return result;
}

bool ArchiListProxy::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    int left_step = sourceModel()->data(left,ArchiList::ArchiListRoles::StepRole).toInt();
    int right_step = sourceModel()->data(right,ArchiList::ArchiListRoles::StepRole).toInt();

    auto archi_stats = static_cast<ArchiList*>(sourceModel())->archiStats();

    return archi_stats->getArchiCapturedInStep(left_step) < archi_stats->getArchiCapturedInStep(right_step);
}

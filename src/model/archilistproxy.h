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

    void showCapturedOnly();
    void showNotCapturedOnly();
    void resetCapturedFilters();

    void sortByStepProgress();
    void resetSortFilters();
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const Q_DECL_OVERRIDE;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const Q_DECL_OVERRIDE;
 private:
    QString name_wanted_;
    bool filter_captured_ = false;
    bool filter_not_captured_ = false;

    bool sort_by_step_progress_ = false;
};

#endif // ARCHILISTPROXY_H

#include "archistats.h"
#include <QDebug>
ArchiStats::ArchiStats(QObject *parent) : QObject(parent)
{

}

void ArchiStats::registerStep(int step)
{
    if (!step_stats_.contains(step)) {
        std::pair<int,int> pair;
        pair.first = 0; pair.second = 0;
        step_stats_[step]= pair;
    }
}

void ArchiStats::increaseTotalArchiCountInStep(int step)
{
    registerStep(step);

    step_stats_[step].second += 1;

}

void ArchiStats::setArchiCount(int count)
{
    total_archi_count_ = count;
}

void ArchiStats::modifyMonsterCapturedInStep(int step, int modif_value)
{
    registerStep(step);

    step_stats_[step].first += modif_value;
}

void ArchiStats::modifyArchiCaptured(int modif_value)
{
    total_captured_archi_ += modif_value;

    emit archiCapturedCountChanged();
}

int ArchiStats::getArchiCapturedCount()
{
    return total_captured_archi_;
}

int ArchiStats::getArchiCount()
{
    return total_archi_count_;
}

int ArchiStats::getArchiCapturedInStep(int step)
{
    if (step_stats_.contains(step) == 0)
        return 0;

    return step_stats_[step].first;
}

int ArchiStats::getTotalArchiCountInStep(int step)
{
    if (step_stats_.contains(step) == 0)
        return 0;

    return step_stats_[step].second;
}

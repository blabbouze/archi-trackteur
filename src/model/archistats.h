#ifndef ARCHISTATS_H
#define ARCHISTATS_H

#include <QObject>
#include <QMap>

class ArchiStats : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int archiCaptured READ getArchiCapturedCount NOTIFY archiCapturedCountChanged)

public:
    explicit ArchiStats(QObject *parent = 0);

    void increaseTotalArchiCountInStep(int step);

    void modifyMonsterCapturedInStep(int step,int modif_value);
    void modifyArchiCaptured(int modif_value);

    int getArchiCapturedCount();
    int getTotalArchiCountInStep(int step);
    int getArchiCapturedInStep(int step);

    // Workaround for refresh archi count by step with QML
    void forceRefreshStepCount();
signals:
    void archiCapturedCountChanged();

    void archiCountInStepChanged(int step, int archi_count);
    void archiCapturedInStepChanged(int step, int archi_captured_count);

 private:
    void registerStep(int step);


    // Step ID => Captured/UnCaptured
    QMap<int,std::pair<int,int>> step_stats_;
    int total_captured_archi_ = 0;
};

#endif // ARCHISTATS_H

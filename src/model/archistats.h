#ifndef ARCHISTATS_H
#define ARCHISTATS_H

#include <QObject>
#include <QMap>

class ArchiStats : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int archiCaptured READ getArchiCapturedCount NOTIFY archiCapturedCountChanged)
    Q_PROPERTY(int archiCount READ getArchiCount NOTIFY archiCountChanged)

public:
    explicit ArchiStats(QObject *parent = 0);

    // Increase the TOTAL count of an archi in a step
    void increaseTotalArchiCountInStep(int step);
    // Set the count of archimonsters
    void setArchiCount(int count);

    // Modify the value of an archimonster in a step.
    // modif_value : 1 if you want to increase archi count
    //              -1 if you want to decrease archi count
    void modifyMonsterCapturedInStep(int step,int modif_value);
    // Modify the vbalue of total archi captured
    // modif_value : 1 if you want to increase archi count
    //              -1 if you want to decrease archi coun
    void modifyArchiCaptured(int modif_value);

    // Get count of captured archi
    int getArchiCapturedCount();
    // Get count of total archi
    int getArchiCount();

public slots:
     int getTotalArchiCountInStep(int step);
     int getArchiCapturedInStep(int step);

signals:
    void archiCapturedCountChanged();
    void archiCountChanged();

 private:
    // Initialize the map with step => pair<0,0>
    void registerStep(int step);


    // Step ID => Captured/UnCaptured
    QMap<int,std::pair<int,int>> step_stats_;
    // Count of captured archi
    int total_captured_archi_ = 0;
    // Total archi count
    int total_archi_count_ = 0;
};

#endif // ARCHISTATS_H

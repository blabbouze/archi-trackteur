#ifndef ARCHILIST_H
#define ARCHILIST_H

#include <QAbstractListModel>
#include <QJsonDocument>

#include "src/io/savefilemanager.h"
#include "archistats.h"
#include <memory>

// Load 2 files :
//  Database file (json)
//  captured archi user file (QList<int> serialized)
//
// Fill json data with user generated file at runtime. This allow
// us to not duplicate database for every user.
class ArchiList : public QAbstractListModel
{
    Q_OBJECT

    Q_PROPERTY(ArchiStats* archiStats READ archiStats NOTIFY archiStatsChanged)
public:
    enum ArchiListRoles {
        ArchiNameRole = Qt::UserRole + 1,
        MonsterNameRole,
        CapturedRole,
        StepRole,
        IDRole
    };

    // Create empty model (needed by qml)
    ArchiList();
    ArchiList(const QString& archi_database_path,
              const QString &captured_archi_path);


    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;


    ArchiStats* archiStats() const;


    void saveUserData();
    void toogleCapturedState(int id_archi);



signals:
    void error(QString explanation);
    void archiStatsChanged();

protected:
    // Do the bridge with qml
    QHash<int, QByteArray> roleNames() const;


private:
    struct Archi {
        int id;
        QString archi_name;
        QString monster_name;
        int step;
        int nb_captured;
    };

    // Fill archi_database_ and archi_size_
    void loadArchiDatabase(const QString &archi_database_path);

    void addArchiToList(const QJsonObject& archi_object);

    void computeStats(const Archi &archi_cpp);


    SaveFileManager file_manager_;
    QList<Archi> archi_list_;
    std::shared_ptr<ArchiStats> stat_manager_;


};


#endif // ARCHILIST_H

#ifndef ARCHILIST_H
#define ARCHILIST_H

#include <QAbstractListModel>
#include <QJsonDocument>


// Load 2 files :
//  Database file (json)
//  captured archi user file (QList<int> serialized)
//
// Fill json data with user generated file at runtime. This allow
// us to not duplicate database for every user.
class ArchiList : public QAbstractListModel
{
    Q_OBJECT


public:
    enum ArchiListRoles {
        ArchiNameRole = Qt::UserRole + 1,
        MonsterNameRole,
        CapturedRole,
        StepRole
    };

    // Create empty model (needed by qml)
    ArchiList();
    ArchiList(const QString& archi_database_path,
              const QString &captured_archi_path);


    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;


    void toogleCapturedState(int id_archi);

signals:
    void error(QString explanation);

protected:
    // Do the bridge with qml
    QHash<int, QByteArray> roleNames() const;


private:

    struct Archi {
        QString archi_name;
        QString monster_name;
        int step;
        bool captured;
    };

    // Fill archi_database_ and archi_size_
    void loadArchiDatabase(const QString &archi_database_path);
    // fill loaded jsonDoc with captured archi ID
    void loadCapturedArchisID(const QString &captured_archi_path);

    QList<Archi> archi_list_;

};


#endif // ARCHILIST_H

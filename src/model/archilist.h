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
        CapturedRole
    };

    // Create empty model (needed by qml)
    ArchiList();
    ArchiList(const QString& archi_database_path,
              const QString &captured_archi_path);


    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;



signals:
    void error(QString explanation);

protected:
    // Do the bridge with qml
    QHash<int, QByteArray> roleNames() const;


private:
    QJsonArray getArchiArray() const;
    // Fill archi_database_ and archi_size_
    void loadArchiDatabase(const QString &archi_database_path);
    // fill captured_archis_id_ if possible
    void loadCapturedArchisID(const QString &captured_archi_path);
   // Fill archi_database_ with data contained in captured_archis_id_
    void fillDatabaseWithCapturedArchis();


    QJsonDocument archi_database_;
    int archi_count_ = 0;

    QList<int> captured_archis_id_;

};


#endif // ARCHILIST_H

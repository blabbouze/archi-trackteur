#include "archilist.h"

#include <QFile>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonArray>


#define KEY_ARCHI_MAIN "archis"
#define KEY_ARCHI_CAPTURED "captured"
#define KEY_ARCHI_ID "id"
#define KEY_ARCHI_NAME_ARCHI "archiName"
#define KEY_ARCHI_NAME_MONSTER "monsterName"

//{"archis": [
//      { "id": 1,
//        "archiName": "bakja",
//        "monsterName": "ddsd",
//      },
//    { "id": 2,
//      "archiName": "bakja",
//      "monsterName": "ddsd",
//    },
//    { "id": 3,
//      "archiName": "bakja",
//      "monsterName": "ddsd",
//    },
//    { "id": 4,
//      "archiName": "bakja",
//      "monsterName": "ddsd",
//    }
//    ]
//}
void ArchiList::fillDatabaseWithCapturedArchis()
{
    if (!archi_database_.isNull())
        return;

    if (archi_database_.isObject())
        return;

    if (captured_archis_id_.count() == 0)
        return;

    auto archiList = getArchiArray();
    QJsonValue fillValue;

    for (auto& archi : archiList) {
        if (archi.toObject().value(KEY_ARCHI_ID).toInt() == captured_archis_id_.first()) {
            captured_archis_id_.pop_front();
            fillValue = true;
        } else {
            fillValue = false;
        }

        archi.toObject().insert(KEY_ARCHI_CAPTURED,fillValue);
    }
}

ArchiList::ArchiList()
{
    // Force archi count to 0
    archi_count_ = 0;
}

ArchiList::ArchiList(const QString &archi_database_path,
                     const QString &captured_archi_path)
{
    loadArchiDatabase(archi_database_path);
    loadCapturedArchisID(captured_archi_path);

    fillDatabaseWithCapturedArchis();
}

int ArchiList::rowCount(const QModelIndex &/*parent*/) const
{
    return archi_count_;
}

QVariant ArchiList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int current_row = index.row();

    auto archiObject = getArchiArray()[current_row].toObject();

    if (role == ArchiNameRole)
        return archiObject.value(KEY_ARCHI_NAME_ARCHI).toString();

    if (role == MonsterNameRole)
        return archiObject.value(KEY_ARCHI_NAME_MONSTER).toString();

    if (role == CapturedRole)
        return archiObject.value(KEY_ARCHI_CAPTURED).toBool();

    return QVariant();
}

QHash<int, QByteArray> ArchiList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ArchiNameRole] = "archiName";
    roles[MonsterNameRole] = "monsterName";
    roles[CapturedRole] = "captured";
    return roles;
}

QJsonArray ArchiList::getArchiArray() const
{
    return archi_database_.object().value(KEY_ARCHI_MAIN).toArray();
}

void ArchiList::loadArchiDatabase(const QString &archi_database_path)
{
    QFile database_file(archi_database_path);
    QJsonParseError errorHandler;

    if (database_file.open(QIODevice::ReadOnly)) {
        archi_database_ = QJsonDocument::fromJson(database_file.readAll(),
                                                  &errorHandler);

        if (errorHandler.error != QJsonParseError::NoError)
            emit error(errorHandler.errorString());

        // This doens't change at runtime
        archi_count_ = getArchiArray().count();
    } else {
         emit error("Couldn't open " + archi_database_path);
    }

}

void ArchiList::loadCapturedArchisID(const QString &captured_archi_path)
{
    QFile captured_archi_file(captured_archi_path);

    if (captured_archi_file.exists()) {
        if (captured_archi_file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&captured_archi_file);
            stream >> captured_archis_id_;
        }
    }
}


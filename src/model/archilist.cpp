#include "archilist.h"

#include <QFile>
#include <QDataStream>
#include <QJsonObject>
#include <QJsonArray>

#include <QDebug>


#define KEY_ARCHI_MAIN "archis"
#define KEY_ARCHI_NAME_ARCHI "archiName"
#define KEY_ARCHI_NAME_MONSTER "monsterName"
#define KEY_ARCHI_STEP "step"

ArchiList::ArchiList()
{
}

ArchiList::ArchiList(const QString &archi_database_path,
                     const QString &captured_archi_path)
{
    loadArchiDatabase(archi_database_path);
    loadCapturedArchisID(captured_archi_path);
}

int ArchiList::rowCount(const QModelIndex &/*parent*/) const
{
    return archi_list_.count();
}

QVariant ArchiList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto archi_data = archi_list_.at(index.row());

    if (role == ArchiNameRole)
        return archi_data.archi_name;

    if (role == MonsterNameRole)
        return archi_data.monster_name;

    if (role == CapturedRole)
        return archi_data.captured;

    if (role == StepRole)
        return archi_data.step;

    return QVariant();
}

void ArchiList::toogleCapturedState(int index)
{
   archi_list_[index].captured = !archi_list_[index].captured;

   emit dataChanged(this->index(index), this->index(index),
           QVector<int>{CapturedRole});
}

QHash<int, QByteArray> ArchiList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ArchiNameRole] = "archiName";
    roles[MonsterNameRole] = "monsterName";
    roles[CapturedRole] = "captured";
    roles[StepRole] = "step";
    return roles;
}


void ArchiList::loadArchiDatabase(const QString &archi_database_path)
{
    QFile database_file(archi_database_path);
    QJsonParseError errorHandler;

    if (database_file.open(QIODevice::ReadOnly)) {
        QJsonDocument archi_database = QJsonDocument::fromJson(database_file.readAll(),
                                                  &errorHandler);

        if (errorHandler.error != QJsonParseError::NoError)
            emit error(errorHandler.errorString());

        QJsonObject archi_object;
        Archi archi_cpp;
        for(auto archi_data: archi_database.object()[KEY_ARCHI_MAIN].toArray()) {
           archi_object  = archi_data.toObject();

           archi_cpp.archi_name = archi_object.value(KEY_ARCHI_NAME_ARCHI).toString();
           archi_cpp.monster_name = archi_object.value(KEY_ARCHI_NAME_MONSTER).toString();
           archi_cpp.step = archi_object.value(KEY_ARCHI_STEP).toInt();
           archi_cpp.captured = false;

           archi_list_.append(archi_cpp);
        }

    } else {
         emit error("Couldn't open " + archi_database_path);
    }

}

void ArchiList::loadCapturedArchisID(const QString &captured_archi_path)
{

    QFile captured_archi_file(captured_archi_path);

    if (captured_archi_file.exists()) {
        // Open index list
        QList<int> captured_archi_index;
        if (captured_archi_file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&captured_archi_file);
            stream >> captured_archi_index;
        }

    }
}


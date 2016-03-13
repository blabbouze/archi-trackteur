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
#define KEY_ARCHI_ID "id"


ArchiList::ArchiList()
{
}

ArchiList::ArchiList(const QString &archi_database_path,
                     const QString &captured_archi_path)
{
    stat_manager_ = std::make_shared<ArchiStats>();

    // Load user preferences
    file_manager_.setDefaultPath(captured_archi_path);
    file_manager_.loadFile();

    loadArchiDatabase(archi_database_path);

    emit archiStatsChanged();
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
        return (archi_data.nb_captured > 0);

    if (role == StepRole)
        return archi_data.step;

    return QVariant();
}

ArchiStats *ArchiList::archiStats() const
{
    return stat_manager_.get();
}

void ArchiList::saveUserData()
{
    file_manager_.archi_indexes.clear();

    for(auto archi_cpp : archi_list_) {
        if (archi_cpp.nb_captured  > 0) {
            file_manager_.archi_indexes.insert(archi_cpp.id,
                                               archi_cpp.nb_captured);
        }
    }
    file_manager_.saveFile();
}

void ArchiList::toogleCapturedState(int index)
{
   archi_list_[index].nb_captured = (archi_list_[index].nb_captured +1)%2;

   auto archi_cpp = archi_list_[index];
   int modify_by = 1;
   if (archi_cpp.nb_captured  == 0) {
       modify_by = -1;
   }

   stat_manager_->modifyArchiCaptured(modify_by);
   stat_manager_->modifyMonsterCapturedInStep(archi_cpp.step,modify_by);


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


void ArchiList::computeStats(const Archi& archi_cpp)
{
    // Fill info if this archi is captured
    if (archi_cpp.nb_captured == 1) {
        stat_manager_->modifyArchiCaptured(1);
        // Increment the step count for this archi
        stat_manager_->modifyMonsterCapturedInStep(archi_cpp.step,1);
    }
    // Total step count
    stat_manager_->increaseTotalArchiCountInStep(archi_cpp.step);
}

void ArchiList::addArchiToList(const QJsonObject &archi_object)
{
    Archi archi_cpp;

    archi_cpp.id = archi_object.value(KEY_ARCHI_ID).toInt();
    archi_cpp.archi_name = archi_object.value(KEY_ARCHI_NAME_ARCHI).toString();
    archi_cpp.monster_name = archi_object.value(KEY_ARCHI_NAME_MONSTER).toString();
    archi_cpp.step = archi_object.value(KEY_ARCHI_STEP).toInt();


    archi_cpp.nb_captured = file_manager_.archi_indexes.value(archi_cpp.id);


    computeStats(archi_cpp);

    archi_list_.append(archi_cpp);
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
        auto archi_array_json = archi_database.object()[KEY_ARCHI_MAIN].toArray();


        for(auto archi_data : archi_array_json) {
            archi_object  = archi_data.toObject();
            addArchiToList(archi_object);
        }

        stat_manager_->forceRefreshStepCount();
    } else {
        emit error("Couldn't open " + archi_database_path);
    }
}


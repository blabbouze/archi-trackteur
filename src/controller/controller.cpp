#include "controller.h"

#include <QQmlEngine>
Controller::Controller(QObject *parent) : QObject(parent)
{
    archi_list_raw_ = std::make_shared<ArchiList>(
                "archidata.json","mesArchis.dat");
    emit archiListRawChanged();

    archi_list_proxy_ = std::make_shared<ArchiListProxy>();
    archi_list_proxy_->setSourceModel(archi_list_raw_.get());

    emit archiListChanged();
    connect(archi_list_raw_.get(),SIGNAL(error(QString)),
            this,SIGNAL(error(QString)));
}

ArchiListProxy *Controller::archiList()
{
    QQmlEngine::setObjectOwnership(archi_list_proxy_.get(),
                                   QQmlEngine::CppOwnership);

    return archi_list_proxy_.get();
}

ArchiList *Controller::archiListRaw()
{
    QQmlEngine::setObjectOwnership(archi_list_raw_.get(),
                                   QQmlEngine::CppOwnership);

    return archi_list_raw_.get();
}

void Controller::toogleArchiCaptured(int id_archi)
{
    archi_list_raw_->toogleCapturedState(id_archi);
}

void Controller::save()
{
    archi_list_raw_->saveUserData();
    emit readyToExit();
}

void Controller::searchArchi(const QString &name)
{
    archi_list_proxy_->searchArchiByName(name);
}


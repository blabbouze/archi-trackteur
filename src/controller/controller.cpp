#include "controller.h"

#include <QQmlEngine>
Controller::Controller(QObject *parent) : QObject(parent)
{
    archi_list_raw_ = std::make_shared<ArchiList>(
                "archidata.json","mesArchis.dat");

    connect(archi_list_raw_.get(),SIGNAL(error(QString)),
            this,SIGNAL(error(QString)));
}

ArchiList *Controller::archiList()
{
    QQmlEngine::setObjectOwnership(archi_list_raw_.get(),
                                   QQmlEngine::CppOwnership);

    return archi_list_raw_.get();
}

void Controller::toogleArchiCaptured(int id_archi)
{
    archi_list_raw_->toogleCapturedState(id_archi);
}


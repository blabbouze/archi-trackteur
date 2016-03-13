#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "src/model/archilist.h"
#include "src/model/archilistproxy.h"

#include <memory>

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ArchiListProxy* archiList READ archiList NOTIFY archiListChanged)
    Q_PROPERTY(ArchiList* archiListRaw READ archiListRaw NOTIFY archiListRawChanged)
public:
    explicit Controller(QObject *parent = 0);
    ArchiListProxy* archiList();
    ArchiList* archiListRaw();

signals:
    void archiListChanged();
    void archiListRawChanged();
    void error(QString errorDesc);
    void readyToExit();

public slots:
    void toogleArchiCaptured(int id_archi);
    void save();
    void searchArchi(const QString& name);

private:
    std::shared_ptr<ArchiListProxy> archi_list_proxy_;
    std::shared_ptr<ArchiList> archi_list_raw_;
};

#endif // CONTROLLER_H

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "src/model/archilist.h"
#include "src/model/archilistproxy.h"

#include <memory>

class Controller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(ArchiList* archiList READ archiList NOTIFY archiListChanged)
public:
    explicit Controller(QObject *parent = 0);
    ArchiList* archiList();

signals:
    void archiListChanged();
    void error(QString errorDesc);

public slots:

private:
    std::shared_ptr<ArchiListProxy> archi_list_proxy_;
    std::shared_ptr<ArchiList> archi_list_raw_;
};

#endif // CONTROLLER_H

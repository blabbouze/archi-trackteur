#ifndef SAVEFILEMANAGER_H
#define SAVEFILEMANAGER_H

#include <QMap>


class SaveFileManager
{

    friend class ArchiList;

public:
    SaveFileManager();

    void setDefaultPath(const QString& path);
    void loadFile(const QString& force_path ="");
    void saveFile(const QString& force_path ="");

private:
    enum Version {
        VERSION_1 = 1
    };

    // Return file_path_ if force_path is empty
    // file_path_ otherwise
    QString getPath(const QString &force_path);

    QString file_path_;


    Version version;
    QMap<int,int> archi_indexes;
};

#endif // SAVEFILEMANAGER_H

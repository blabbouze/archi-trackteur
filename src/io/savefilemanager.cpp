#include "savefilemanager.h"

#include <QFile>
#include <QDataStream>

SaveFileManager::SaveFileManager()
{
    version = VERSION_1;
}

void SaveFileManager::setDefaultPath(const QString &path)
{
    file_path_ = path;
}

void SaveFileManager::loadFile(const QString &force_path)
{
    QString path = getPath(force_path);

    QFile captured_archi_file(path);

    if (captured_archi_file.exists()) {
        if (captured_archi_file.open(QIODevice::ReadOnly)) {
            QDataStream stream(&captured_archi_file);
            int v;
            stream >> v;
            stream >> archi_indexes;

            version = (SaveFileManager::Version) v;
        }
    }
}

void SaveFileManager::saveFile(const QString &force_path)
{
    QString path = getPath(force_path);
    QFile captured_archi_file(path);

    if (captured_archi_file.open(QIODevice::WriteOnly)) {
        QDataStream stream(&captured_archi_file);
        stream << version;
        stream << archi_indexes;
    }
}

QString SaveFileManager::getPath(const QString &force_path)
{
    QString path_used = file_path_;
    if (!force_path.isEmpty())
        path_used = force_path;

    return path_used;
}

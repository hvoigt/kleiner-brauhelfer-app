#include "syncservicedemo.h"
#include <QFile>

SyncServiceDemo::SyncServiceDemo(QSettings *settings) :
    SyncService(settings)
{
    setFilePath(cacheFilePath(QStringLiteral("__kb_daten_demo__.sqlite")));
    if (!QFile::exists(getFilePath()))
    {
        QFile srcFile(":/data/kb_daten.sqlite");
        if (!srcFile.open(QIODevice::ReadOnly))
            return;
        QFile dstFile(getFilePath());
        if (dstFile.open(QIODevice::WriteOnly))
        {
            dstFile.write(srcFile.readAll());
            dstFile.close();
        }
        srcFile.close();
    }
}

bool SyncServiceDemo::synchronize(SyncDirection direction)
{
    if (!QFile::exists(getFilePath()))
    {
        QFile srcFile(":/data/kb_daten.sqlite");
        if (srcFile.open(QIODevice::ReadOnly))
        {
            QFile dstFile(getFilePath());
            if (dstFile.open(QIODevice::WriteOnly))
            {
                dstFile.write(srcFile.readAll());
                dstFile.close();
            }
            srcFile.close();
        }
    }

    if (QFile::exists(getFilePath()))
    {
        if (direction == SyncDirection::Download)
        {
            setState(SyncState::UpToDate);
        }
        else
        {
            setState(SyncState::Updated);
        }
        return true;
    }
    else
    {
        setState(SyncState::NotFound);
        return false;
    }
}

void SyncServiceDemo::clearCache()
{
    QFile file(getFilePath());
    file.remove();
}

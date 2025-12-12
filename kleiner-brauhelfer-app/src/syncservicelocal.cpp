#include "syncservicelocal.h"
#include <QFile>
#ifndef Q_OS_ANDROID
  #include <QUrl>
  #include <QDir>
#endif

QString SyncServiceLocal::toLocalFile(const QString &url)
{
  #ifdef Q_OS_ANDROID
    return url;
  #else
    return QDir::toNativeSeparators(QUrl(url).toLocalFile());
  #endif
}

SyncServiceLocal::SyncServiceLocal(QSettings *settings) :
    SyncService(settings)
{
  #ifdef Q_OS_ANDROID
    setFilePath(cacheFilePath(QStringLiteral("__kb_daten_local__.sqlite")));
  #else
    setFilePath(_settings->value("SyncService/local/DatabasePath").toString());
  #endif
}

SyncServiceLocal::SyncServiceLocal(const QString &filePath) :
    SyncService(nullptr)
{
  #ifdef Q_OS_ANDROID
    setFilePath(cacheFilePath(QStringLiteral("__kb_daten_local__.sqlite")));
  #else
    setFilePath(filePath);
  #endif
}

bool SyncServiceLocal::synchronize(SyncDirection direction)
{
    if (QFile::exists(filePathLocal()))
    {
        if (direction == SyncDirection::Download)
        {
          #ifdef Q_OS_ANDROID
            QFile srcFile(filePathLocal());
            if (!srcFile.open(QIODevice::ReadOnly))
                return false;
            QFile dstFile(getFilePath());
            if (dstFile.open(QIODevice::WriteOnly))
            {
                dstFile.write(srcFile.readAll());
                dstFile.close();
            }
            srcFile.close();
          #endif
            setState(SyncState::UpToDate);
        }
        else
        {
          #ifdef Q_OS_ANDROID
            QFile srcFile(getFilePath());
            if (!srcFile.open(QIODevice::ReadOnly))
                return false;
            QFile dstFile(filePathLocal());
            if (dstFile.open(QIODevice::WriteOnly))
            {
                dstFile.write(srcFile.readAll());
                dstFile.close();
            }
            srcFile.close();
          #endif
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

QString SyncServiceLocal::filePathLocal() const
{
    return _settings->value("SyncService/local/DatabasePath").toString();
}

void SyncServiceLocal::setFilePathLocal(const QString &filePath)
{
    if (filePathLocal() != filePath)
    {
      #ifndef Q_OS_ANDROID
        setFilePath(filePath);
      #endif
        _settings->setValue("SyncService/local/DatabasePath", filePath);
        emit filePathLocalChanged(filePath);
    }
}

void SyncServiceLocal::clearCache()
{
  #ifdef Q_OS_ANDROID
    QFile file(getFilePath());
    file.remove();
  #endif
}

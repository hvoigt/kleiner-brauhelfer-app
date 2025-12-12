#ifndef SYNCSERVICELOCAL_H
#define SYNCSERVICELOCAL_H

#include "syncservice.h"
#include <QObject>
#include <QSettings>

/**
 * @brief Local file synchronization service
 */
class SyncServiceLocal : public SyncService
{
    Q_OBJECT

    Q_PROPERTY(QString filePathLocal READ filePathLocal WRITE setFilePathLocal NOTIFY filePathLocalChanged)

public:

    /**
     * @brief Returns a string representing a local path from an URL
     * @param url URL
     * @return Local file path
     */
    Q_INVOKABLE static QString toLocalFile(const QString &url);

    /**
     * @brief Local file synchronization service
     * @param settings Settings
     */
    SyncServiceLocal(QSettings *settings);

    /**
     * @brief Local file synchronization service
     * @param filePath File path
     */
    SyncServiceLocal(const QString &filePath);

    /**
     * @brief  Synchronizes the file
     * @param direction Direction to synchronize
     * @note See getState() for details about the synchronization state
     * @return True on success
     */
    bool synchronize(SyncDirection direction) Q_DECL_OVERRIDE;

    /**
     * @brief Gets the database path on the server
     * @return Database path
     */
    QString filePathLocal() const;

    /**
     * @brief Sets the database path on the server
     * @param filePath Database path
     */
    void setFilePathLocal(const QString &filePath);

    /**
     * @brief Clears the whole cache
     * @note All local files will be deleted
     */
    Q_INVOKABLE virtual void clearCache() Q_DECL_OVERRIDE;

signals:

    /**
     * @brief Emitted if database path on the server changed
     * @param filePath Database path
     */
    void filePathLocalChanged(const QString &filePath);
};

#endif // SYNCSERVICELOCAL_H

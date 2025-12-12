#ifndef SYNCSERVICEDEMO_H
#define SYNCSERVICEDEMO_H

#include "syncservice.h"
#include <QObject>
#include <QSettings>

/**
 * @brief Demo file service
 */
class SyncServiceDemo : public SyncService
{
    Q_OBJECT

public:

    /**
     * @brief Demo file service
     * @param settings Settings
     */
    SyncServiceDemo(QSettings *settings);

    /**
     * @brief Synchronizes the file
     * @param direction Direction to synchronize
     * @note See getState() for details about the synchronization state
     * @return True on success
     */
    bool synchronize(SyncDirection direction) Q_DECL_OVERRIDE;

    /**
     * @brief Clears the whole cache
     * @note All local files will be deleted
     */
    Q_INVOKABLE virtual void clearCache() Q_DECL_OVERRIDE;
};

#endif // SYNCSERVICEDEMO_H

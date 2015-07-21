#ifndef TORRENTOBSERVER_H
#define TORRENTOBSERVER_H
#include "ArgoLoader.h"
#include <QList>
#include <QObject>

class TorrentListObserver : public Argo::IUniverseEventObserver
{
public:
        TorrentListObserver(QList<QObject*>& torrList);
        virtual void onTorrentAdded(const Argo::SHA1Hash &hash);
        virtual void onTorrentRemoved(const Argo::SHA1Hash &hash);

private:
        QList<QObject*>& _torrent_list;
};

class TorrentFileObserver : public Argo::ITorrentEventObserver {
public:
    virtual void onMetadataReceived() override;
    virtual void onPieceCompleted(int piece) override;
    virtual void onTorrentCompleted() override;
    virtual void onTorrentReaped() override;
};

#endif // TORRENTOBSERVER_H

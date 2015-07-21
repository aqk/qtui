#ifndef TORRENTOBSERVER_H
#define TORRENTOBSERVER_H
#include "ArgoLoader.h"

class TorrentListObserver : public Argo::IUniverseEventObserver
{
public:
        virtual void onTorrentAdded(const Argo::SHA1Hash &hash);
        virtual void onTorrentRemoved(const Argo::SHA1Hash &hash);
};

class TorrentFileObserver : public Argo::ITorrentEventObserver {
public:
    virtual void onMetadataReceived() override;
    virtual void onPieceCompleted(int piece) override;
    virtual void onTorrentCompleted() override;
    virtual void onTorrentReaped() override;
};

#endif // TORRENTOBSERVER_H

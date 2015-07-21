#ifndef TORRENTOBSERVER_H
#define TORRENTOBSERVER_H
#include "ArgoLoader.h"

class TorrentListObserver : public Argo::IUniverseEventObserver
{
public:
        virtual void onTorrentAdded(const Argo::SHA1Hash &hash);
        virtual void onTorrentRemoved(const Argo::SHA1Hash &hash);
};
#endif // TORRENTOBSERVER_H


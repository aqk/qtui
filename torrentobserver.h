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
#endif // TORRENTOBSERVER_H


#include "torrentobserver.h"
#include "qtorrentobject.h"
using namespace Argo;


TorrentListObserver::TorrentListObserver(QList<QObject*>& torrList) :
    _torrent_list(torrList) {
}

void TorrentListObserver::onTorrentAdded(const Argo::SHA1Hash &hash)
{
    _torrent_list.append(new QTorrentObject("A torrent.torrent", 1000));
    printf("Torrent Added\n");
}

void TorrentListObserver::onTorrentRemoved(const Argo::SHA1Hash &hash)
{
        printf("Torrent Removed\n");
}


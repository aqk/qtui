#include "torrentobserver.h"

using namespace Argo;

void TorrentListObserver::onTorrentAdded(const Argo::SHA1Hash &hash)
{
        printf("Torrent Added\n");
}

void TorrentListObserver::onTorrentRemoved(const Argo::SHA1Hash &hash)
{
        printf("Torrent Removed\n");
}


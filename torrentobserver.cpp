#include "torrentobserver.h"
#include "qtorrentobject.h"
using namespace Argo;


TorrentListObserver::TorrentListObserver(QList<QObject*>& torrList) :
    _torrent_list(torrList) {
}

void TorrentListObserver::onTorrentAdded(const Argo::SHA1Hash &hash)
{
    _torrent_list.append(new QTorrentObject("dummy.torrent", 0));
    printf("Torrent Added\n");
}

void TorrentListObserver::onTorrentRemoved(const Argo::SHA1Hash &hash)
{
        printf("Torrent Removed\n");
}

void TorrentFileObserver::onMetadataReceived() {
    // Ignore for now
    printf("Metadata Received");
}

void TorrentFileObserver::onPieceCompleted(int piece) {
    // In here, let's find our torrent in the collection,
    // and update its display text to reflect % complete (e.g. str += "67%")
    printf("Piece %d Completed", piece);
}

void TorrentFileObserver::onTorrentCompleted() {
    printf("Torrent Completed");
}

void TorrentFileObserver::onTorrentReaped() {
    printf("Torrent Reaped");
}

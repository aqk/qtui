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

void TorrentFileObserver::onMetadataReceived() {
    printf("Metadata Received");
}

void TorrentFileObserver::onPieceCompleted(int piece) {
    printf("Piece %d Completed", piece);
}

void TorrentFileObserver::onTorrentCompleted() {
    printf("Torrent Completed");
}

void TorrentFileObserver::onTorrentReaped() {
    printf("Torrent Reaped");
}

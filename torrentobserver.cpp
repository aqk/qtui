#include "torrentobserver.h"
#include "qtorrentobject.h"
using namespace Argo;

#include "qtorrentobject.h"


TorrentListObserver::TorrentListObserver(QTorrentListModel* torrList) :
    _qt_list_model(torrList) {
}

void TorrentListObserver::onTorrentAdded(const Argo::SHA1Hash &hash)
{
    QSharedPointer<QTorrentObject> torrent(new QTorrentObject);
    _qtorrent_list.append(torrent);

    torrent->setName(hash.value);
    torrent->setTotalBytes(1000);
    torrent->setStatus(QTorrentObject::Status::DOWNLOADING);
    _qt_list_model->append(torrent);
    _qt_list_model->notifyOfUpdate(torrent);
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

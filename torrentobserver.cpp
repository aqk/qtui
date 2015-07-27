#include "torrentobserver.h"

#include "qtorrentobject.h"
#include "argoqmlcontext.h"
#include "ArgoLoader.h"

TorrentListObserver::TorrentListObserver(QTorrentListModel* torrList) :
    _qt_list_model(torrList)
{
}

void TorrentListObserver::onTorrentAdded(const Argo::SHA1Hash &hash)
{
    extern ArgoQMLContext g_argoQmlContext;
    std::shared_ptr<ArgoQMLContext::TorrentContext> t_ctx = g_argoQmlContext.addTorrent(hash);

    t_ctx->q_torrent = QSharedPointer<QTorrentObject>::create();

    //_qtorrent_list.append(torrent);

    //torrent->setName(hash.value);
    t_ctx->q_torrent->setTotalBytes(0);
    t_ctx->q_torrent->setHash(hash);
    t_ctx->q_torrent->setStatus(QTorrentObject::Status::DOWNLOADING);
    _qt_list_model->append(t_ctx->q_torrent);
    _qt_list_model->notifyOfUpdate(t_ctx->q_torrent);

    printf("Torrent Added\n");
}

void TorrentListObserver::onTorrentRemoved(const Argo::SHA1Hash &hash)
{
        printf("Torrent Removed\n");
}

TorrentFileObserver::TorrentFileObserver(const Argo::SHA1Hash &hash)
    : _hash(hash), _q_torrent_object(nullptr)
{
}

void TorrentFileObserver::onMetadataReceived() {
    // Ignore for now
    printf("Metadata Received");
}

void TorrentFileObserver::onPieceCompleted(int piece) {
    // In here, let's find our torrent in the collection,
    // and update its display text to reflect % complete (e.g. str += "67%")
    printf("Piece %d Completed", piece);
    extern ArgoQMLContext g_argoQmlContext;

    std::shared_ptr<ArgoQMLContext::TorrentContext> torrent_ctx = g_argoQmlContext.lookupTorrent(_hash);

    QTorrentListModel* tlm = g_argoQmlContext.getTorrentListModel();
    if(!_q_torrent_object) {
         _q_torrent_object = torrent_ctx->q_torrent;
    }

    if(torrent_ctx->argo_torrent && _q_torrent_object) {
        int length = torrent_ctx->argo_torrent->GetLength();
        int numPieces = torrent_ctx->argo_torrent->GetNumPieces();
        int pieceSize = torrent_ctx->argo_torrent->GetPieceSize();
        int downloaded = _q_torrent_object->piecesDownloaded() + 1;
        _q_torrent_object->setName(torrent_ctx->name);
        _q_torrent_object->setPieceSize(pieceSize);
        _q_torrent_object->setTotalPieces(numPieces);
        _q_torrent_object->setPiecesDownloaded(downloaded);
        _q_torrent_object->setBytesDownloaded(pieceSize * downloaded);
        _q_torrent_object->setTotalBytes(length);
        g_argoQmlContext.getTorrentListModel()->notifyOfUpdate(_q_torrent_object);
        printf("Torrent Added\n");
    }
}

void TorrentFileObserver::onTorrentCompleted() {
    printf("Torrent Completed");
}

void TorrentFileObserver::onTorrentReaped() {
    printf("Torrent Reaped");
}

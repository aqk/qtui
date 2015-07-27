#include <QMessageBox>

#include "argoqmlcontext.h"

ArgoQMLContext::ArgoQMLContext(QObject *parent) : QObject(parent),
    _universe(nullptr)
{
}

void ArgoQMLContext::loadTorrentClicked(const QString &filePath)
{
    // Create the universe the first time we load a torrent
    if(!_universe) {
        _universe = Argo::Universe::Load(L"OldCoreShim.dll");
        if (!_universe) {
            QMessageBox::information(NULL, "Error! Error!", "Failed to load OldCoreShim.dll");
            return;
        }
        _universe->SetDataRoot(L".");
        _tlo = std::shared_ptr<TorrentListObserver>(new TorrentListObserver(&_qt_list_model));
        _universe->AddObserver(_tlo.get());
    }

    // Add button was clicked. Go ahead and let argo know.
    std::wstring path = filePath.toStdWString().c_str();

    std::shared_ptr<Argo::Torrent> torrent = _universe->LoadTorrent(path);
    if(!torrent) {
        QMessageBox::information(NULL, "Error! Error!", "Failed to load torrent!");
        return;
    }
    int index = filePath.lastIndexOf('\\');
    if(index == -1) {
        index = filePath.lastIndexOf('/');
    }

    QString f_name = filePath.mid(index + 1);
    Argo::SHA1Hash hash = torrent->GetInfoHash();
    std::shared_ptr<TorrentContext> t_ctx = addTorrent(hash);
    t_ctx->argo_torrent = torrent;
    t_ctx->name = f_name;
    t_ctx->q_torrent->setName(f_name);

    torrent->AddObserver(new TorrentFileObserver(hash));
    torrent->Start();

    // Test NotifyBytesUpdated
    NotifyOfBytesReceived(1000);

    NotifyOfTotalProgress(49);
}

std::shared_ptr<ArgoQMLContext::TorrentContext> ArgoQMLContext::lookupTorrent(const Argo::SHA1Hash& hash)
{
    std::map<Argo::SHA1Hash, std::shared_ptr<ArgoQMLContext::TorrentContext>>::iterator it = _torrents.find(hash);
    if(it == _torrents.end()) {
        return nullptr;
    }
    return _torrents[hash];
}

std::shared_ptr<ArgoQMLContext::TorrentContext> ArgoQMLContext::addTorrent(const Argo::SHA1Hash &hash)
{
    std::shared_ptr<TorrentContext> t_ctx = std::make_shared<TorrentContext>();
    if(_torrents.find(hash) != _torrents.end()) {
        return _torrents[hash];
    }
    _torrents[hash] = t_ctx;
    return t_ctx;
}

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
    torrent->AddObserver(new TorrentFileObserver());
    _torrents.push_back(torrent);
    torrent->Start();

    // Test NotifyBytesUpdated
    NotifyOfBytesReceived(1000);
}


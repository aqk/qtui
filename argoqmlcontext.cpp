#include <QMessageBox>

#include "argoqmlcontext.h"
#include "torrentobserver.h"

ArgoQMLContext::ArgoQMLContext(QObject *parent) : QObject(parent)
{
    _universe = Argo::Universe::Load(L"OldCoreShim.dll");
    if (!_universe) {
        // TODO: Can't do this because we have no QApplication yet...
        QMessageBox::information(NULL, "Error! Error!", "Failed to load OldCoreShim.dll");
    }
    _universe->SetDataRoot(L".");
}

void ArgoQMLContext::loadTorrentClicked(const QString &filePath)
{
    // Add button was clicked. Go ahead and let argo know.
    // TODO: Add code here

    std::wstring path = filePath.toStdWString().c_str();
    std::shared_ptr<Argo::Torrent> torrent = _universe->LoadTorrent(path);
    if(!torrent) {
        QMessageBox::information(NULL, "Error! Error!", "Failed to load torrent!");
        return;
    }
    torrent->AddObserver(new TorrentFileObserver());
    _torrents.push_back(torrent);
    torrent->Start();
}


#include "mainwindow.h"

#include <condition_variable>
#include <memory>

#include <QApplication>
#include <QMessageBox>

#include "ArgoLoader.h"
#include "torrentobserver.h"

using namespace Argo;
#if 0
class TorrentListObserver : public Argo::IUniverseEventObserver
{
public:
        virtual void onTorrentAdded(const Argo::SHA1Hash &hash)
        {
                printf("Torrent Added\n");
        }

        virtual void onTorrentRemoved(const Argo::SHA1Hash &hash)
        {
                printf("Torrent Removed\n");
        }
};
#endif
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QString torrent_file = w.LoadTorrentPicker();

    // Note: need wide string
    std::shared_ptr<Argo::Universe> universe = Argo::Universe::Load(L"argo.dll");

    if (!universe) {
        QMessageBox::information(NULL, "Error! Error!", "Failed to load argo.dll");
        return a.exec();
    }

    // XXX Calling SetDataRoot currently explodes
    universe->SetDataRoot(L".");
    TorrentListObserver torrentListObserver;

    universe->AddObserver(&torrentListObserver);

    std::shared_ptr<Argo::Torrent> torrent = universe->LoadTorrent(torrent_file.toStdWString().c_str());

    std::mutex wait_mutex;
    std::condition_variable wait_for_torrent_complete;

    torrent->Start();

    return a.exec();
}

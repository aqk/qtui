#include "mainwindow.h"

#include <memory>

#include <QApplication>
#include <QMessageBox>
#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QList>

#include "ArgoLoader.h"
#include "torrentobserver.h"
#include "qtorrentobject.h"

using namespace Argo;
void setupQmlContextByValue(QQmlApplicationEngine& engine) {
    // Dummy model and data
    QList<QObject*> torrList;
    torrList.append(new QTorrentObject("A torrent.torrent", 1000));
    torrList.append(new QTorrentObject("B Torrent.torrent", 2000));

    // Get root context from the engine
    QQmlContext* rootCtx = engine.rootContext();
    rootCtx->setContextProperty("downloadListModel", QVariant::fromValue(torrList));
    // TODO: Pass actual top peer state
    rootCtx->setContextProperty("topPeersList", QVariant::fromValue(torrList));
}

int main(int argc, char *argv[])
{
    // Dummy data
    QList<QObject*> torrList;
    torrList.append(new QTorrentObject("CCCC torrent.torrent", 1000));

    // Load the argo DLL
    std::shared_ptr<Argo::Universe> universe(Argo::Universe::Load(L"OldCoreShim.dll"));
    universe->SetDataRoot(L".");
    TorrentListObserver torrentListObserver(torrList);
    universe->AddObserver(&torrentListObserver);

    // Load the main qml
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    if (!universe) {
        QMessageBox::information(NULL, "Error! Error!", "Failed to load OldCoreShim.dll");
        return -1;
    }

    // Load 2 torrents
    QString torrent1_path("../qtui/CentOS-6.6-x86_64-minimal.ova.torrent");
    QString torrent2_path("../qtui/ubuntu-15.04-desktop-amd64.iso.torrent");

    std::shared_ptr<Argo::Torrent> torrent1 = universe->LoadTorrent(torrent1_path.toStdWString().c_str());
    std::shared_ptr<Argo::Torrent> torrent2 = universe->LoadTorrent(torrent2_path.toStdWString().c_str());

    torrent1->Start();
    torrent2->Start();

    // Setup a by-value context
    // TODO: Tie in classes
    setupQmlContextByValue(engine);

    // Load the root qml
    engine.load(QUrl(QStringLiteral("qrc:///ltdash.qml")));

    // Run the application loop
    return app.exec();
}

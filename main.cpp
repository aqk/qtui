#include "mainwindow.h"

#include <memory>

#include <QApplication>
#include <QMessageBox>
#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QList>
#include <QtConcurrent/QtConcurrent>

#include "ArgoLoader.h"
#include "torrentobserver.h"
#include "qtorrentlistmodel.h"
#include "argoqmlcontext.h"
using namespace Argo;

ArgoQMLContext g_argoQmlContext;

// TODO: This does not need to be global
//QTorrentListModel g_torrentModel;

void InitializeQMLContext(QQmlApplicationEngine& engine) {
    // Dummy model and data

//    QSharedPointer<QTorrentObject> t1Obj(new QTorrentObject);
//    QSharedPointer<QTorrentObject> t2Obj(new QTorrentObject);

//    t1Obj->setName("Torrent A");
//    t1Obj->setTotalBytes(1000);
//    t2Obj->setName("Torrent B");
//    t2Obj->setTotalBytes(20000);

//    // Appends an initial copy
//    g_torrentModel.append(t1Obj);
//    g_torrentModel.append(t2Obj);

    // Get root context from the engine
    QQmlContext* rootCtx = engine.rootContext();
    rootCtx->setContextProperty("downloadListModel", g_argoQmlContext.getTorrentListModel().get());
    // TODO: add a peers list model

    rootCtx->setContextProperty("argoContext", &g_argoQmlContext);
}

int main(int argc, char *argv[])
{
    // Load the main qml
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Dummy data
    QList<QObject*> torrList;
    TorrentListObserver* tlo = new TorrentListObserver(torrList);
    std::shared_ptr<Argo::Universe> universe = g_argoQmlContext.getUniverse();
    universe->AddObserver(tlo);
    //torrList.append(new QTorrentObject("CCCC torrent.torrent", 1000));

    // Load the argo DLL
   /*
    std::shared_ptr<Argo::Universe> universe(Argo::Universe::Load(L"OldCoreShim.dll"));
    universe->SetDataRoot(L".");
    TorrentListObserver torrentListObserver(torrList);
    universe->AddObserver(&torrentListObserver);
*/
/*
    if (!universe) {
        QMessageBox::information(NULL, "Error! Error!", "Failed to load OldCoreShim.dll");
        return -1;
    }

    // Load 2 torrents
*/
//    QString torrent1_path("../qtui/CentOS-6.6-x86_64-minimal.ova.torrent");
//    QString torrent2_path("../qtui/ubuntu-15.04-desktop-amd64.iso.torrent");

//    std::shared_ptr<Argo::Torrent> torrent1 = universe->LoadTorrent(torrent1_path.toStdWString().c_str());
//    std::shared_ptr<Argo::Torrent> torrent2 = universe->LoadTorrent(torrent2_path.toStdWString().c_str());

//    torrent1->Start();
//    torrent2->Start();

    // Setup context
    InitializeQMLContext(engine);


    //QSharedPointer<QTorrentObject> t3Obj(new QTorrentObject);
    //t3Obj->setName("Torrent C");
    //g_torrentModel.append(t3Obj);

    // TODO: REMOVE. This is an incredibly silly (and unsafe) example.
    // Wait 2 seconds then update the torrent name. Let the model
    // know the data updated
//    QtConcurrent::run([t3Obj] {
//        QThread::sleep(1);
//        t3Obj->setName("Torrent DDD");
//        g_torrentModel.notifyOfUpdate(t3Obj);
//    });

    // Load the root qml
    engine.load(QUrl(QStringLiteral("qrc:///ltdash.qml")));

    // Run the application loop
    return app.exec();
}

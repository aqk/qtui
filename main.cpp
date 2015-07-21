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
    // Load the argo DLL
    std::shared_ptr<Argo::Universe> universe(Argo::Universe::Load(L"OldCoreShim.dll"));

    // Load the main qml
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    if (!universe) {
        QMessageBox::information(NULL, "Error! Error!", "Failed to load OldCoreShim.dll");
        return -1;
    }

    // Setup a by-value context
    // TODO: Tie in classes
    setupQmlContextByValue(engine);

    // Load the root qml
    engine.load(QUrl(QStringLiteral("qrc:///ltdash.qml")));

    // Run the application loop
    return app.exec();
}

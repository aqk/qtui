#include "mainwindow.h"

#include <memory>

#include <QApplication>
#include <QMessageBox>
#include <QGuiApplication>
#include <QtQml/QQmlApplicationEngine>
#include <QtQml/QQmlContext>
#include <QList>
#include <QtConcurrent/QtConcurrent>

#include "argoqmlcontext.h"
using namespace Argo;

ArgoQMLContext g_argoQmlContext;

void InitializeQMLContext(QQmlApplicationEngine& engine) {
    // Get root context from the engine
    QQmlContext* rootCtx = engine.rootContext();
    rootCtx->setContextProperty("downloadListModel", g_argoQmlContext.getTorrentListModel());
    // TODO: add a peers list model

    rootCtx->setContextProperty("argoContext", &g_argoQmlContext);
}

int main(int argc, char *argv[])
{
    // Load the main qml
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Setup context
    InitializeQMLContext(engine);

    // Add qml to the path. Support jbQuick.Charts 1.0
    engine.addImportPath(QStringLiteral("qml"));
    // Load the root qml
    engine.load(QUrl(QStringLiteral("qrc:///ltdash.qml")));

    // Run the application loop
    return app.exec();
}

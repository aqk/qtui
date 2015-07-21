#include "mainwindow.h"

#include <memory>

#include <QApplication>
#include <QMessageBox>

#include "ArgoLoader.h"
#include "torrentobserver.h"

using namespace Argo;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    std::shared_ptr<Argo::Universe> universe(Argo::Universe::Load(L"OldCoreShim.dll"));

    if (!universe) {
        QMessageBox::information(NULL, "Error! Error!", "Failed to load OldCoreShim.dll");
        return a.exec();
    }

    w.setUniverse(universe);

    w.show();

    return a.exec();
}

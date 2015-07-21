#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

#include <condition_variable>

using namespace Argo;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

QString MainWindow::LoadTorrentPicker() {
    return QFileDialog::getOpenFileName(this, tr("Open Torrent"), "", tr("Torrents (*.torrent)"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUniverse(const std::shared_ptr<Argo::Universe>& universe) {
    _universe = universe;
}

void MainWindow::on_pushButton_clicked()
{
    QString torrent_file = LoadTorrentPicker();

    // XXX Calling SetDataRoot currently explodes
    _universe->SetDataRoot(L".");

    TorrentListObserver torrentListObserver(_torrList);

    _universe->AddObserver(&torrentListObserver);

    std::shared_ptr<Argo::Torrent> torrent = _universe->LoadTorrent(torrent_file.toStdWString().c_str());

    if (!torrent) {
        QMessageBox::information(NULL, "Error! Error!", "Failed to load Torrent: [torrent name]");
        return;
    }

    // Temporary storage until we get the listview ready
    _torrents.push_back(torrent);

    // Don't think we'll need these
    std::mutex wait_mutex;
    std::condition_variable wait_for_torrent_complete;

    torrent->Start();
}

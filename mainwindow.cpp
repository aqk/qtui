#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

QString MainWindow::LoadTorrentPicker() {
    return QFileDialog::getOpenFileName(this,
        tr("Open Torrent"), "", tr("Torrents (*.torrent)"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

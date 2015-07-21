#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <memory>

#include "ArgoLoader.h"
#include "torrentobserver.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString MainWindow::LoadTorrentPicker();
    ~MainWindow();

    void setUniverse(const std::shared_ptr<Argo::Universe>& universe);

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<Argo::Universe> _universe;
    std::vector<std::shared_ptr<Argo::Torrent> > _torrents;
};

#endif // MAINWINDOW_H

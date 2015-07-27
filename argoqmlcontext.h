#ifndef ARGOQMLCONTEXT_H
#define ARGOQMLCONTEXT_H

#include <QObject>

#include <memory>
#include "ArgoLoader.h"
#include "qtorrentlistmodel.h"
#include "torrentobserver.h"

class ArgoQMLContext : public QObject
{
    Q_OBJECT
public:
    explicit ArgoQMLContext(QObject *parent = 0);
    Q_INVOKABLE void loadTorrentClicked( const QString& filePath);
    void NotifyOfBytesReceived(int bytes) { emit bytesReceived(bytes); }
    void NotifyOfTotalProgress(int progress) { emit totalProgress(progress); }
    std::shared_ptr<Argo::Universe> getUniverse() const { return _universe; }
    QTorrentListModel* getTorrentListModel() { return &_qt_list_model; }

signals:
    void bytesReceived(int bytes);
    void totalProgress(int progress);
public slots:
private:
    std::shared_ptr<Argo::Universe> _universe;
    QTorrentListModel _qt_list_model;
    std::vector<std::shared_ptr<Argo::Torrent> > _torrents;
    std::shared_ptr<TorrentListObserver> _tlo;
};

#endif // ARGOQMLCONTEXT_H

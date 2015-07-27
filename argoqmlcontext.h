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
    // This just holds the info we need for a torrent in one place
    class TorrentContext {
    public:
        TorrentContext() :
            name(QString::null), argo_torrent(nullptr)
        {
            q_torrent = QSharedPointer<QTorrentObject>::create();
        }
        QString name;
        QSharedPointer<QTorrentObject> q_torrent;
        std::shared_ptr<Argo::Torrent> argo_torrent;
    };

    explicit ArgoQMLContext(QObject *parent = 0);
    Q_INVOKABLE void loadTorrentClicked( const QString& filePath);
    void NotifyOfBytesReceived(int bytes) { emit bytesReceived(bytes); }
    void NotifyOfTotalProgress(int progress) { emit totalProgress(progress); }
    std::shared_ptr<Argo::Universe> getUniverse() const { return _universe; }
    QTorrentListModel* getTorrentListModel() { return &_qt_list_model; }

    std::shared_ptr<TorrentContext> lookupTorrent(const Argo::SHA1Hash& hash);
    std::shared_ptr<TorrentContext> addTorrent(const Argo::SHA1Hash& hash);

signals:
    void bytesReceived(int bytes);
    void totalProgress(int progress);
public slots:
private:

    std::shared_ptr<Argo::Universe> _universe;
    QTorrentListModel _qt_list_model;
    std::map<Argo::SHA1Hash, std::shared_ptr<TorrentContext>> _torrents;
    std::shared_ptr<TorrentListObserver> _tlo;
};

#endif // ARGOQMLCONTEXT_H

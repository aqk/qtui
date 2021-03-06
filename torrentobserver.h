#ifndef TORRENTOBSERVER_H
#define TORRENTOBSERVER_H
#include "ArgoLoader.h"
#include <QList>
#include <QObject>

#include "qtorrentlistmodel.h"

class TorrentListObserver : public Argo::IUniverseEventObserver
{
public:
        TorrentListObserver(QTorrentListModel* torrList);
        virtual void onTorrentAdded(const Argo::SHA1Hash &hash);
        virtual void onTorrentRemoved(const Argo::SHA1Hash &hash);

private:
        QTorrentListModel* _qt_list_model;
        //QList<QSharedPointer<QTorrentObject> > _qtorrent_list;
};

class TorrentFileObserver : public Argo::ITorrentEventObserver {
public:
    TorrentFileObserver(const Argo::SHA1Hash &hash);
    virtual void onMetadataReceived() override;
    virtual void onPieceCompleted(int piece) override;
    virtual void onTorrentCompleted() override;
    virtual void onTorrentReaped() override;

private:
    Argo::SHA1Hash _hash;
    QSharedPointer<QTorrentObject> _q_torrent_object;
};

#endif // TORRENTOBSERVER_H

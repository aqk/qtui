#include "qtorrentlistmodel.h"
#include "qtorrentobject.h"
QTorrentListModel::QTorrentListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    // Map role names to string equivalents accesible from qml
    m_roleNames[NameRole] = "name";
    m_roleNames[SpeedRole] = "speed";
    m_roleNames[TotalBytesRole] = "totalBytes";
    m_roleNames[BytesDownloadedRole] = "bytesDownloaded";
    m_roleNames[dateTimeAddedRole] = "dateTimeAdded";
    m_roleNames[torrentStatusRole] = "torrentStatus";
}

int QTorrentListModel::rowCount(const QModelIndex &parent) const
{
    return m_torrents.count();
}

QVariant QTorrentListModel::data(const QModelIndex &index, int role) const {
    // Boilerplate bounds checking on the index
    int row = index.row();
    if (row < 0 || row >= m_torrents.count()) {
        return QVariant();
    }

    QSharedPointer<QTorrentObject> torrent = m_torrents.at(row);
    switch(role) {
        case NameRole:
            return torrent->name();
        case SpeedRole:
            return torrent->speed();
        case TotalBytesRole:
            return torrent->totalBytes();
        case BytesDownloadedRole:
            return torrent->bytesDownloaded();
        case dateTimeAddedRole:
            return torrent->dateTimeAdded();
        case torrentStatusRole:
            return torrent->torrentStatus();
    }

    // Fallthrough
    return QVariant();

}


bool QTorrentListModel::insert(int insert_index, QSharedPointer<QTorrentObject>torrent)
{

    if (insert_index < 0|| insert_index > m_torrents.count())
        return false;

    // Notify before insert, insert, notify after insert
    emit beginInsertRows(QModelIndex(), insert_index, insert_index);
    m_torrents.insert(insert_index, torrent);
    emit countChanged(m_torrents.count());
    emit endInsertRows();
    return true;
}

QSharedPointer<QTorrentObject> QTorrentListModel::get(int index)
{
    // Boilerplate bounds checking on the index (copied from data())
    int row = index;
    if (row < 0 || row >= m_torrents.count()) {
        return QSharedPointer<QTorrentObject>();
    }

    return m_torrents.at(row);
}

bool QTorrentListModel::append(QSharedPointer<QTorrentObject> torrent)
{
    insert(count(), torrent);
    return true;
}

int QTorrentListModel::count()
{
    return m_torrents.count();
}

void QTorrentListModel::notifyOfUpdate(QSharedPointer<QTorrentObject> torrent)
{
    int collectionIndex = m_torrents.indexOf(torrent);
    if (collectionIndex != -1) {
        QModelIndex modelIndex = index(collectionIndex);
        QModelIndex endIndex = index(m_torrents.count() - 1);
        // Notify QML of changes
        emit dataChanged(modelIndex, endIndex);
    }
}

QHash<int, QByteArray> QTorrentListModel::roleNames() const {
    return m_roleNames;
}

QSharedPointer<QTorrentObject> QTorrentListModel::lookupTorrent(const Argo::SHA1Hash &hash) {
    QList<QSharedPointer<QTorrentObject>>::iterator it =
            std::find_if(m_torrents.begin(), m_torrents.end(), [hash] (QSharedPointer<QTorrentObject> t) { return t->hash() == hash; } );
    return it == m_torrents.end() ? QSharedPointer<QTorrentObject>() : (*it);
}


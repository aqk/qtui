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
    }

    // Fallthrough
    return QVariant();

}


bool QTorrentListModel::insert(int index, QSharedPointer<QTorrentObject>torrent)
{

    if (index < 0|| index > m_torrents.count())
        return false;

    // Notify before insert, insert, notify after insert
    emit beginInsertRows(QModelIndex(), index, index);
    m_torrents.insert(index, torrent);
    emit countChanged(m_torrents.count());
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



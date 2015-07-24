#ifndef QTORRENTLISTMODEL_H
#define QTORRENTLISTMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QList>
#include <QHash>
#include <QSharedPointer>


#include "qtorrentobject.h"

class QTorrentListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    enum RoleNames {
        NameRole = Qt::UserRole,
        SpeedRole = Qt::UserRole+2,
        TotalBytesRole = Qt::UserRole+3,
        BytesDownloadedRole = Qt::UserRole+4,
        dateTimeAddedRole = Qt::UserRole+5
    };
    explicit QTorrentListModel(QObject *parent = 0);

    ~QTorrentListModel() {}
public:
    // This is the interface for QAbstractListModel
    // How many rows do we have (optimized rendering)
    virtual int rowCount(const QModelIndex &parent) const override;
    // Return data from the role and index given
    virtual QVariant data(const QModelIndex &index, int role) const override;

    // Add insertion
    bool insert(int insert_index, QSharedPointer<QTorrentObject> torrent);
    bool append(QSharedPointer<QTorrentObject> torrent);
    QSharedPointer<QTorrentObject> get(int index);
    int count();
    void notifyOfUpdate(QSharedPointer<QTorrentObject> torrent);
protected:
    virtual QHash<int, QByteArray> roleNames() const override;
signals:
    void countChanged(int newCount);
private:
    QList<QSharedPointer<QTorrentObject>> m_torrents;
    QHash<int, QByteArray> m_roleNames;
};

#endif //  QTORRENTLISTMODEL_H

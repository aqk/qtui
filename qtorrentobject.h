#ifndef QTORRENTOBJECT_H
#define QTORRENTOBJECT_H

#include <QObject>

class QTorrentObject : public QObject
{
    Q_OBJECT
public:
    explicit QTorrentObject(QObject *parent = 0);
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int downloadedBytes READ downloadedBytes WRITE setDownloadedBytes NOTIFY downloadedBytesChanged)
    QTorrentObject(const QString& name, int dled);

    void setName(const QString& name) {
        this->m_name = name;
        emit nameChanged(name);
    }
    void setDownloadedBytes(int dledBytes) {
        this->m_downloadedBytes = dledBytes;
        emit downloadedBytesChanged(dledBytes);
    }

    QString name() { return m_name; }
    int downloadedBytes() { return m_downloadedBytes; }
private:
    QString m_name;
    int m_downloadedBytes;

signals:
    void nameChanged(QString newName);
    void downloadedBytesChanged(int dled);

public slots:
};

#endif // QTORRENTOBJECT_H

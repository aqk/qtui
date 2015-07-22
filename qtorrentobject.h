#ifndef QTORRENTOBJECT_H
#define QTORRENTOBJECT_H

#include <QObject>

class QTorrentObject : public QObject
{
    Q_OBJECT
public:
    explicit QTorrentObject(QObject *parent = 0);
    QTorrentObject(const QString& name, int totalBytes);
    QTorrentObject(const QTorrentObject& obj);
    Q_PROPERTY(QString name         READ name            WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int speed            READ speed           WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int totalBytes       READ totalBytes      WRITE setTotalBytes NOTIFY totalBytesChanged)
    Q_PROPERTY(int bytesDownloaded  READ bytesDownloaded WRITE setBytesDownloaded NOTIFY bytesDownloadedChanged)

    // Getters/Setters
    int bytesDownloaded() const;
    void setBytesDownloaded(int bytesDownloaded);

    int totalBytes() const;
    void setTotalBytes(int totalBytes);

    int speed() const;
    void setSpeed(int speed);

    QString name() const;
    void setName(const QString &name);

signals:
    void nameChanged(QString newName);
    void speedChanged(int newSpeed);
    void totalBytesChanged(int newTotalBytes);
    void bytesDownloadedChanged(int newBytesDownloaded);

public slots:
private:
    QString m_name;
    int m_speed;
    int m_totalBytes;
    int m_bytesDownloaded;
};

#endif // QTORRENTOBJECT_H

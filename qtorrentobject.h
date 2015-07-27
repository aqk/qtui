#ifndef QTORRENTOBJECT_H
#define QTORRENTOBJECT_H

#include <QObject>
#include <QDate>

class QTorrentObject : public QObject
{
    Q_OBJECT
public:
    explicit QTorrentObject(QObject *parent = 0);
    QTorrentObject(const QString& name, int totalBytes);
    QTorrentObject(const QTorrentObject& obj);

    enum Status { WAITING, DOWNLOADING, SEEDING, DONE };
    Q_PROPERTY(QString name             READ name            WRITE setName              NOTIFY nameChanged)
    Q_PROPERTY(int speed                READ speed           WRITE setSpeed             NOTIFY speedChanged)
    Q_PROPERTY(int totalBytes           READ totalBytes      WRITE setTotalBytes        NOTIFY totalBytesChanged)
    Q_PROPERTY(int bytesDownloaded      READ bytesDownloaded WRITE setBytesDownloaded   NOTIFY bytesDownloadedChanged)
    Q_PROPERTY(QDateTime dateTimeAdded  READ dateTimeAdded   WRITE setdateTimeAdded     NOTIFY dateTimeAddedChanged)
    Q_PROPERTY(Status status            READ status          WRITE setStatus            NOTIFY statusChanged)
    Q_ENUM(Status)

    // Getters/Setters
    int bytesDownloaded() const;
    void setBytesDownloaded(int bytesDownloaded);

    int totalBytes() const;
    void setTotalBytes(int totalBytes);

    int speed() const;
    void setSpeed(int speed);

    QString name() const;
    void setName(const QString &name);

    QDateTime dateTimeAdded() const;
    void setdateTimeAdded(const QDateTime &dateTimeAdded);

    void setStatus(Status status);
    int status() const;

signals:
    void nameChanged(QString newName);
    void speedChanged(int newSpeed);
    void totalBytesChanged(int newTotalBytes);
    void bytesDownloadedChanged(int newBytesDownloaded);
    void dateTimeAddedChanged(QDateTime newdateTimeAdded);
    void statusChanged(Status status);
public slots:
private:
    QString m_name;
    int m_speed;
    int m_totalBytes;
    int m_bytesDownloaded;
    QDateTime m_dateTimeAdded;
    Status m_status;
};

#endif // QTORRENTOBJECT_H

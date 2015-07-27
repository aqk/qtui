#ifndef QTORRENTOBJECT_H
#define QTORRENTOBJECT_H

#include <QObject>
#include <QDate>

#include "ArgoLoader.h"

class QTorrentObject : public QObject
{
    Q_OBJECT
public:
    explicit QTorrentObject(QObject *parent = 0);
    QTorrentObject(const QString& name, int totalBytes);
    QTorrentObject(const QTorrentObject& obj);

    Q_PROPERTY(QString name             READ name            WRITE setName              NOTIFY nameChanged)
    Q_PROPERTY(int speed                READ speed           WRITE setSpeed             NOTIFY speedChanged)
    Q_PROPERTY(int totalBytes           READ totalBytes      WRITE setTotalBytes        NOTIFY totalBytesChanged)
    Q_PROPERTY(int bytesDownloaded      READ bytesDownloaded WRITE setBytesDownloaded   NOTIFY bytesDownloadedChanged)
    Q_PROPERTY(QDateTime dateTimeAdded  READ dateTimeAdded   WRITE setdateTimeAdded     NOTIFY dateTimeAddedChanged)
    Q_PROPERTY(QString status           READ status          WRITE setStatus            NOTIFY statusChanged)

    // Getters/Setters
    int bytesDownloaded() const;
    void setBytesDownloaded(int bytesDownloaded);

    int piecesDownloaded() const;
    void setPiecesDownloaded(int piecesDownloaded);

    int totalBytes() const;
    void setTotalBytes(int totalBytes);

    int totalPieces() const;
    void setTotalPieces(int totalPieces);

    void setPieceSize(int pieceSize);

    int speed() const;
    void setSpeed(int speed);

    QString name() const;
    void setName(const QString &name);

    const Argo::SHA1Hash& hash() const;
    void setHash(const Argo::SHA1Hash &hash);

    QDateTime dateTimeAdded() const;
    void setdateTimeAdded(const QDateTime &dateTimeAdded);

    void setStatus(const QString& status);
    QString status() const;

signals:
    void nameChanged(QString newName);
    void speedChanged(int newSpeed);
    void totalBytesChanged(int newTotalBytes);
    void bytesDownloadedChanged(int newBytesDownloaded);
    void dateTimeAddedChanged(QDateTime newdateTimeAdded);
    void statusChanged(QString status);
public slots:
private:
    QString m_name;
    int m_speed;
    int m_totalBytes;
    int m_total_pieces;
    int m_have_pieces;
    int m_bytesDownloaded;
    int m_pieceSize;
    QDateTime m_dateTimeAdded;
    Argo::SHA1Hash m_hash;
    QString m_status;
};
#endif // QTORRENTOBJECT_H

#include "qtorrentobject.h"

QTorrentObject::QTorrentObject(QObject *parent) : QObject(parent)
  , m_name(""), m_speed(0), m_totalBytes(0), m_bytesDownloaded(0)
{

}

QTorrentObject::QTorrentObject(const QString &name, int totalBytes)
    : QTorrentObject()
{
    m_name = name;
    m_totalBytes = totalBytes;
}


QTorrentObject::QTorrentObject(const QTorrentObject &obj) {
    m_name = obj.m_name;
    m_speed = obj.m_speed;
    m_totalBytes = obj.m_totalBytes;
    m_bytesDownloaded = obj.m_bytesDownloaded;

}

int QTorrentObject::bytesDownloaded() const
{
    return m_bytesDownloaded;
}

void QTorrentObject::setBytesDownloaded(int bytesDownloaded)
{
    m_bytesDownloaded = bytesDownloaded;
    emit bytesDownloadedChanged(bytesDownloaded);
}
int QTorrentObject::totalBytes() const
{
    return m_totalBytes;
}

void QTorrentObject::setTotalBytes(int totalBytes)
{
    m_totalBytes = totalBytes;
    emit totalBytesChanged(totalBytes);
}
int QTorrentObject::speed() const
{
    return m_speed;
}

void QTorrentObject::setSpeed(int speed)
{
    m_speed = speed;
    emit speedChanged(speed);
}
QString QTorrentObject::name() const
{
    return m_name;
}

void QTorrentObject::setName(const QString &name)
{
    m_name = name;
    emit nameChanged(name);
}






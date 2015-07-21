#include "qtorrentobject.h"

QTorrentObject::QTorrentObject(QObject *parent)
    : QObject(parent)
{

}

#include "qtorrentobject.h"

QTorrentObject::QTorrentObject(const QString& name, int dled)
    : m_name(name), m_downloadedBytes(dled)
{

}


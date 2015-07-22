#ifndef ARGOQMLCONTEXT_H
#define ARGOQMLCONTEXT_H

#include <QObject>

#include <memory>
#include "ArgoLoader.h"
#include "qtorrentlistmodel.h"

class ArgoQMLContext : public QObject
{
    Q_OBJECT
public:
    explicit ArgoQMLContext(QObject *parent = 0);
    Q_INVOKABLE void loadTorrentClicked( const QString& filePath);

    std::shared_ptr<Argo::Universe> getUniverse() const { return _universe; }
    std::shared_ptr<QTorrentListModel> getTorrentListModel() const { return _qt_list_model; }

signals:

public slots:
private:
    std::shared_ptr<Argo::Universe> _universe;
    std::shared_ptr<QTorrentListModel> _qt_list_model;
};

#endif // ARGOQMLCONTEXT_H

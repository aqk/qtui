#ifndef ARGOQMLCONTEXT_H
#define ARGOQMLCONTEXT_H

#include <QObject>

class ArgoQMLContext : public QObject
{
    Q_OBJECT
public:
    explicit ArgoQMLContext(QObject *parent = 0);
    Q_INVOKABLE void loadTorrentClicked( const QString& filePath);

signals:

public slots:
private:
    // Have an instance of the Argo::Universe here?

    // Have a QTorrentListModel here?
};

#endif // ARGOQMLCONTEXT_H

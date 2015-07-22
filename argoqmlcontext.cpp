#include <QMessageBox>

#include "argoqmlcontext.h"

ArgoQMLContext::ArgoQMLContext(QObject *parent) : QObject(parent)
{

}

void ArgoQMLContext::loadTorrentClicked(const QString &filePath)
{
    // Add button was clicked. Go ahead and let argo know.
    // TODO: Add code here
    QMessageBox box;
    box.setText("Testing");
    box.exec();
}


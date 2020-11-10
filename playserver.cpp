#include "playserver.h"
#include <QDataStream>

PlayServer::PlayServer(QObject *parent)
    :QTcpServer(parent),
      plist(new QMediaPlaylist(this))
{
}

void PlayServer::readCommand()
{
    QByteArray block;

}

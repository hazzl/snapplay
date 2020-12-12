#include "playthread.h"
#include "playserver.h"
#include <QVariant>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

PlayThread::PlayThread(quintptr socketDescriptor, QObject *parent)
    :QThread(parent),
      socketDescriptor(socketDescriptor)
{
    connect (this, &QThread::finished, this, &QThread::deleteLater);
    db.addDatabase("MARIADB");
    db.setHostName("localhost");
    db.setDatabaseName("rucqus");
    db.setUserName("rucqusUser");
    db.setPassword("rucqusPassword");
    if (!db.open())
    {
        qDebug() << db.lastError().text();
        emit error(QTcpSocket::ConnectionRefusedError);
    }
}

PlayThread::~PlayThread()
{
    db.close();
}

void PlayThread::run()
{
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }
    there.setDevice(&tcpSocket);
    there.setVersion(QDataStream::Qt_5_15);
    connect (&tcpSocket, &QTcpSocket::readyRead, this, &PlayThread::readCommand);
    connect (&tcpSocket, &QTcpSocket::errorOccurred, this, &PlayThread::onError);
}

void PlayThread::onError(QTcpSocket::SocketError socketError)
{
    qDebug() << "ERROR" << socketError;
    emit error(socketError);
}

void PlayThread::readCommand()
{
    PlayServer::Command com;
    QVariant arg;
    there.startTransaction();
    there >> com >> arg;
    if (!there.commitTransaction()) // if there was not enough data to read both obejcts
        return;                     // wait for more data

    PlayServer *server = static_cast<PlayServer *>(this->parent());
    switch (com) {
        case PlayServer::AddMedia: {
            qDebug() << "rec AddMedia " << arg.toUInt();
            QSqlQuery q;
            q.prepare("SELECT path FROM songs WHERE id = ?");
            q.addBindValue(arg);
            q.exec();
            server->addMedia(q.value(0).toString());
            break;
        }
        case PlayServer::Play:
            qDebug("rec play");
            server->play();
            break;
        default: // not implemented
            emit error(QTcpSocket::OperationError);
    }
}

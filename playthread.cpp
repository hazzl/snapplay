#include "playthread.h"
#include "playserver.h"
#include <QVariant>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

PlayThread::PlayThread(PlayServer* server, qintptr socketDescriptor, QObject *parent)
    :QThread(nullptr),
      server{server},
      socketDescriptor{socketDescriptor}
{
    Q_UNUSED(parent);
    connect (this, &QThread::finished, this, &QThread::deleteLater);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMARIADB");
    if(!db.isDriverAvailable("QMARIADB"))
        qDebug() << "availble drivers:" << db.drivers();
    db.setHostName("localhost");
    db.setDatabaseName("rucqus");
    db.setUserName("rucqususer");
    db.setPassword("rucquspassword");
    if (!db.isValid())
        qDebug("invalid database");
    if (!db.open())
    {
        QSqlError err = db.lastError();
        qDebug() << "db:" << err.databaseText() << "driver:" << err.driverText();
        emit error(QTcpSocket::ConnectionRefusedError);
    }
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

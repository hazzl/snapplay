#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDataStream>
#include <QSqlDatabase>
#include <playserver.h>

class PlayThread : public QThread
{
    Q_OBJECT
public:
    explicit PlayThread(PlayServer* server, qintptr socketDescriptor, QObject *parent = nullptr);
    ~PlayThread();
    void run() override;
signals:
    void error(QTcpSocket::SocketError socketError);
private:
    PlayServer *server;
    const qintptr socketDescriptor;
    QDataStream there;
    QTcpSocket tcpSocket;
    QSqlDatabase db;
private slots:
    void readCommand();
    void onError(QTcpSocket::SocketError socketError);
};

#endif // PLAYTHREAD_H

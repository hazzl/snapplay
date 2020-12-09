#ifndef PLAYTHREAD_H
#define PLAYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDataStream>
#include <QSqlDatabase>

class PlayThread : public QThread
{
    Q_OBJECT
public:
    explicit PlayThread(quintptr socketDescriptor, QObject *parent = nullptr);
    ~PlayThread();
    void run() override;
signals:
    void error(QTcpSocket::SocketError socketError);
private:
    int socketDescriptor;
    QDataStream there;
    QTcpSocket tcpSocket;
    QSqlDatabase db;
private slots:
    void readCommand();
    void onError(QTcpSocket::SocketError socketError);
};

#endif // PLAYTHREAD_H

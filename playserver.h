#ifndef PLAYSERVER_H
#define PLAYSERVER_H

#include <QTcpServer>
#include <QMediaPlaylist>
#include <QDataStream>
class PlayServer : public QTcpServer
{
    Q_OBJECT
public:
    enum Command {AddMedia, DelMedia, GetPlaylist, Play, Pause, Status, Duration, Seek, Next, Prev, SetCurrent};
    Q_ENUM(Command);
    explicit PlayServer(QObject* partent=nullptr);
private slots:
    void readCommand();
private:
    QMediaPlaylist *plist=nullptr;
    QDataStream in;
};
#endif // PLAYSERVER_H

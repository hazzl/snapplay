#ifndef PLAYSERVER_H
#define PLAYSERVER_H

#include <QString>
#include <QMediaPlaylist>
#include <QTcpServer>
#include "decoder.h"

class PlayServer : public QTcpServer
{
    Q_OBJECT
public:
    enum Command {AddMedia, DelMedia, GetPlaylist, Play, Pause, Status, Duration, Seek, Next, Prev, SetCurrent};
    Q_ENUM(Command);
    explicit PlayServer(QObject* partent=nullptr);
    void incomingConnection(qintptr socketDescriptor) override;
public slots:
    void addMedia(const QString &path);
    void play();
    //void pause();
private slots:
    void onNewMedia(const QMediaContent &content);
private:
    QMediaPlaylist *plist;
    Decoder *decoder;
};
#endif // PLAYSERVER_H

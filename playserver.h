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
    enum Command {AddMedia,     //arg: quint32 = song_id ´
                  DelMedia,     //arg: quint32 = playlist_index ; return = NULL
                  GetPlaylist,  //arg: NULL; return QVector<quint32> = song_id
                  Play,         // arg: NULL; return = NULL
                  Pause,        // arg: NULL; return = NULL
                  Status,       // arg: NULL: return = QDecoder::State
                  Duration,     // arg: NULL: return = quint32 = duration_msecs
                  Seek,         // arg: quint32 = point_msecs
                  Next,
                  Prev,
                  SetCurrent};
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

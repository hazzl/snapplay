#include "playserver.h"
#include "playthread.h"
#include <QUrl>
#include <QMediaContent>
#include <QDebug>

PlayServer::PlayServer(QObject *parent)
    :QTcpServer(parent)
{
    plist = new QMediaPlaylist(this);
    decoder = new Decoder(this);
    connect(decoder, &QAudioDecoder::finished, plist, &QMediaPlaylist::next);
    connect(plist, &QMediaPlaylist::currentMediaChanged, this, &PlayServer::onNewMedia);
}

void PlayServer::onNewMedia(const QMediaContent &content)
{
    decoder->setSourceFilename(content.request().url().toLocalFile());
    decoder->start();
}

void PlayServer::incomingConnection(qintptr socketDescriptor)
{
    PlayThread *t = new PlayThread(socketDescriptor, this);
    t->start();
}

void PlayServer::addMedia(const QString &path)
{
    qDebug() << "adding " << path ;
    QUrl url;
    QMediaContent *content;
    url.fromLocalFile(path);
    content = new QMediaContent(url);
    plist->addMedia(*content);
}

void PlayServer::play()
{
    if (decoder->state() == QAudioDecoder::StoppedState)
        decoder->start();
}

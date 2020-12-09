#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QObject>
#include <QVector>

class Playlist : public QObject
{
    Q_OBJECT
public:
    explicit Playlist(QObject *parent = nullptr);

signals:

private:
    QVector<quint32> *m_plist;
};
#endif // PLAYLIST_H

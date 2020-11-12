#ifndef DECODER_H
#define DECODER_H

#include <QAudioDecoder>
#include <QFile>

class Decoder : public QAudioDecoder
{
    Q_OBJECT
public:
    Decoder(QObject *parent = nullptr);
    ~Decoder();
private:
    QFile out;
private slots:
    void copyBuffer();
};

#endif // DECODER_H

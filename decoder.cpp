#include "decoder.h"
#include <QAudioFormat>

Decoder::Decoder(QObject *parent)
    :QAudioDecoder(parent)
{
    out.setFileName("/tmp/snapfifo");
    if (!out.exists())
    {
        //throw error
        qFatal("couldn't find fifo");
        emit error(QAudioDecoder::AccessDeniedError);
    }
    if(!out.open(QIODevice::WriteOnly))
    {
        qFatal("couldn't open fifo");
        emit error(QAudioDecoder::AccessDeniedError);
    }
    QAudioFormat fmt;
    fmt.setSampleRate(48000);
    fmt.setSampleSize(16);
    fmt.setChannelCount(2);
    fmt.setSampleType(QAudioFormat::SignedInt);
    fmt.setByteOrder(QAudioFormat::LittleEndian);
    fmt.setCodec("audio/pcm");
    this->setAudioFormat(fmt);

    connect (this, &QAudioDecoder::bufferReady, this, &Decoder::copyBuffer);
}

Decoder::~Decoder()
{
    out.close();
}

void Decoder::copyBuffer()
{
    QAudioBuffer buf;
    buf = read();
    if(buf.isValid())
    {
        const char *c = reinterpret_cast<const char*>(buf.constData());
        qint64 w, written = 0;
        int bytes = buf.byteCount();
        do {
            w = out.write(c + written, bytes - written);
            written += w;
        } while ((written < bytes) && !(w < 0));
        if (w < 0)
        {
            qFatal("write error");
            emit error(QAudioDecoder::ResourceError);
        }
    }
}

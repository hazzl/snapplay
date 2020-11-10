#include <QCoreApplication>
#include "decoder.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Decoder d;

    d.setSourceFilename("/srv/daten/Musik/xiaoxingxing.ogg");
    a.connect(&d, SIGNAL(Decoder::error(QAudioDecoder::Error e)), &a, SLOT(QCoreApplication::quit()));
    a.connect(&d, SIGNAL(Decoder::finished()), &a, SLOT(QCoreApplication::quit()));
    d.start();

    return a.exec();
}

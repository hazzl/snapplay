#include <QCoreApplication>
#include "decoder.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Decoder d;

    d.setSourceFilename("/srv/daten/Musik/xiaoxingxing.ogg");
    a.connect(&d, SIGNAL(error(QAudioDecoder::Error)), &a, SLOT(quit()));
    a.connect(&d, SIGNAL(finished()), &a, SLOT(quit()));
    d.start();

    return a.exec();
}

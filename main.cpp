#include <QCoreApplication>
#include <QSqlDatabase>
#include "decoder.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Decoder d(&a);
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("rucqus");
    db.setUserName("rucqusUser");
    db.setPassword("rucqusPassword");
    if (db.open())
    {

    d.setSourceFilename("/srv/daten/Musik/xiaoxingxing.ogg");
    a.connect(&d, SIGNAL(error(QAudioDecoder::Error)), &a, SLOT(quit()));
    a.connect(&d, SIGNAL(finished()), &a, SLOT(quit()));
    d.start();

    return a.exec();
    }
}

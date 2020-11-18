#include <QCoreApplication>
#include "playserver.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    PlayServer p(&a);
    if(p.listen(QHostAddress::Any,23975))
        return a.exec();
    else
        qFatal("couldn't start server");
}

#include "progavprinc.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ProgAvPrinc w;
    w.show();

    return a.exec();
}

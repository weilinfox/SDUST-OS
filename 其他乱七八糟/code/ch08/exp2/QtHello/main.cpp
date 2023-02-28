#include "winhello.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WinHello w;
    w.show();

    return a.exec();
}

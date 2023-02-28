#include "qdlgmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDlgMain w;
    w.show();

    return a.exec();
}

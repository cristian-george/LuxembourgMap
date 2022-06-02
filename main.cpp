#include "LuxembourgMap.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LuxembourgMap w;
    w.showMaximized();
    return a.exec();
}

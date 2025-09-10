#include "FiveStarPlayerVS.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    FiveStarPlayerVS w;
    w.show();
    return a.exec();
}
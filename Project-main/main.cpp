#include "screenmenu.h"

#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScreenMenu w;
    w.show();
    return a.exec();
}

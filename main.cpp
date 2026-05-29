#include "myimageedit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyImageEdit w;
    w.show();
    return a.exec();
}

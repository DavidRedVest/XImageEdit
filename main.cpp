#include "myimageedit.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //设置全局应用程序图标,这是windows版本
   // a.setWindowIcon(QIcon("/Resources/logo.ico"));
    //mac版本
    a.setWindowIcon(QIcon("/Resources/apple_logo.icns"));

    MyImageEdit w;
    w.show();
    return a.exec();
}

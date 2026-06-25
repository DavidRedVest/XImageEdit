#include <QApplication>

#include "myimageedit.h"

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

#if defined(Q_OS_WIN)
    a.setWindowIcon(QIcon(":/Resources/logo.ico"));
#elif defined(Q_OS_MACOS)
    // macOS：Dock 图标由 CMake 的 MACOSX_BUNDLE_ICON_FILE 控制
    // 这里设置的是关于对话框/窗口标题栏图标，用 Qt 资源里的 png 即可
    a.setWindowIcon(
        QIcon(":/Resources/logo1.png"));  // 或者专门准备一个 app_icon.png
#else
    a.setWindowIcon(QIcon(":/Resources/logo.ico"));
#endif

    MyImageEdit w;
    w.show();
    return a.exec();
}

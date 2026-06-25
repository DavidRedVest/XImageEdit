#ifndef XIMAGE_H
#define XIMAGE_H

#include <QImage>
#include <QWidget>

#include "constants.h"
class IController;

class XImage : public QWidget {
    Q_OBJECT

   public:
    XImage(QWidget* p = 0);
    ~XImage();

    // 重载绘制方法 update后会调用
    void paintEvent(QPaintEvent* e);

    // 重载鼠标函数
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);

   public slots:
    void Open();
    void SetPen();
    void SetErase();
    void SetRect();
    void Undo();
    void Redo();
    void SetPenSize(int size);
    void SetPenColor(int r, int g, int b, int a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }
    void SavePicture();

   protected:
    // IController* c = 0;
    std::unique_ptr<IController> c;

    // int penSize = 5;
    // int r = 200;
    // int g = 0;
    // int b = 0;
    // int a = 255;  // 不透明

    int penSize = AppConfig::DEFAULT_PEN_SIZE;
    int r = AppConfig::DEFAULT_COLOR_R;
    int g = AppConfig::DEFAULT_COLOR_G;
    int b = AppConfig::DEFAULT_COLOR_B;
    int a = AppConfig::DEFAULT_COLOR_A;  // 不透明
};

#endif  // XIMAGE_H

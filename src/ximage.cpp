#include "ximage.h"

#include <QDebug>
#include <QFileDialog>
#include <QMouseEvent>
#include <QPainter>
// #include "xeditview.h"
#include <QFileInfo>

#include "icontroller.h"
#include "xcontrollerfactory.h"
#include "xmodel.h"

// XModel m;

XImage::XImage(QWidget* p) : QWidget(p) {
    // c = IController::Create(new XControllerFactory());
    c.reset(IController::Create(&XControllerFactory::getInstance()));
    if (c) {
        c->Init(this);
    }
}

XImage::~XImage() {
}

void XImage::Open() {
    // 打开图片
    QString filename = QFileDialog::getOpenFileName(
        this, QStringLiteral("打开图片"), "",
        QStringLiteral("支持的格式(*.png *.jpg *.bmp)"));
    if (filename.isEmpty()) {
        qDebug() << "Open filename is empty!";
        return;
    }
    // 加载图片
    QByteArray path = filename.toLocal8Bit();
    if (!c || !c->InitBack(path.constData())) {
        qDebug() << "src.load image failed!";
        return;
    }
    // 显示通知，刷新滚动条布局
    if (this->parentWidget()) {
        this->parentWidget()->update();
    }

    // 刷新显示
    update();
}

void XImage::SetPen() {
    if (c) {
        c->SetStatus(XPEN);
    }
}
void XImage::SetErase() {
    if (c) {
        c->SetStatus(XERASER);
    }
}
void XImage::SetRect() {
    if (c) {
        c->SetStatus(XRECT);
    }
}

void XImage::Undo() {
    if (c) {
        c->Undo();
    }
    // 刷新显示
    update();
}
void XImage::Redo() {
    if (c) {
        c->Redo();
    }
    // 刷新显示
    update();
}
void XImage::SetPenSize(int size) {
    penSize = size;
}

void XImage::SavePicture(void) {
    QString filename = QFileDialog::getSaveFileName(
        this, QStringLiteral("保存图片"), "",
        QStringLiteral("PNG图片 （*.png);;JPG图片（*.jpg);;BMP图片（*.bmp)"));
    if (filename.isEmpty()) {
        qDebug() << "Save filename is empty, cancel save.";
        return;
    }
#if 1
    // 检查并将之补全后缀名
    QFileInfo fileInfo(filename);
    if (fileInfo.suffix().isEmpty()) {
        // 如果用户没有加后缀，默认加上.png
        filename += ".png";
    }
    // 使用局部保存变量 QByteArray，防止指针悬空
    QByteArray ba = filename.toUtf8();

#endif

    // 调用控制器，将平台相关的 QString 转换为统一的 const char*
    if (c && c->Save(ba.constData())) {
        qDebug() << "Image saved successfully to:" << filename;
    } else {
        qDebug() << "Failed to save image!";
    }
}
// 鼠标重载函数
void XImage::mousePressEvent(QMouseEvent* e) {
    if (!c) {
        return;
    }
    c->AddModel();
    c->SetPara("size", penSize);
    c->SetPara("r", r);
    c->SetPara("g", g);
    c->SetPara("b", b);
    c->SetPara("a", a);
    c->Add(e->position().x(), e->position().y());
}
// 默认鼠标移动事件，按下才触发
void XImage::mouseMoveEvent(QMouseEvent* e) {
    if (!c) {
        return;
    }
    c->Add(e->position().x(), e->position().y());
    update();
}

void XImage::mouseReleaseEvent(QMouseEvent* e) {
    Q_UNUSED(e);
    if (!c) {
        return;
    }
    // 告诉控制器：这一笔画完了，固化图层
    c->FinishModel();
    // 触发最后一次UI刷新
    update();
}

void XImage::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);
    if (c) {
        c->Paint();
    }
}

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

XImage::XImage(QWidget* p) : QWidget(p)
{
    c = IController::Create(new XControllerFactory());
    c->Init(this);

    // XEditView::getInstance().InitDevice(this);
    // 视图观察模型
    // m.Attach(&XEditView::getInstance());
}

XImage::~XImage()
{
}

void XImage::Open()
{
    // qDebug() << "XImage::Open()" ;

    // 打开图片
    QString filename = QFileDialog::getOpenFileName(
        this, QStringLiteral("打开图片"), "",
        QStringLiteral("支持的格式(*.png *.jpg *.bmp)"));
    if (filename.isEmpty())
    {
        qDebug() << "Open filename is empty!";
        return;
    }
    // 加载图片
    // if(!src.load(filename)) {
    // if(!XEditView::getInstance().InitBack(filename.toLocal8Bit())) {
    if (!c->InitBack(filename.toLocal8Bit()))
    {
        qDebug() << "src.load image failed!";
        return;
    }
    // qDebug()<<"src.load image successful!";

    // 显示通知，刷新滚动条布局
    if (this->parentWidget())
    {
        this->parentWidget()->update();
    }

    // 刷新显示
    update();
}

void XImage::SetPen()
{
    c->SetStatus(XPEN);
}
void XImage::SetErase()
{
    c->SetStatus(XERASER);
}
void XImage::SetRect()
{
    c->SetStatus(XRECT);
}

void XImage::Undo()
{
    c->Undo();
    // 刷新显示
    update();
}
void XImage::Redo()
{
    c->Redo();
    // 刷新显示
    update();
}
void XImage::SetPenSize(int size)
{
    penSize = size;
}

void XImage::SavePicture(void)
{
    QString filename = QFileDialog::getSaveFileName(
        this, QStringLiteral("保存图片"), "",
        QStringLiteral("PNG图片 （*.png);;JPG图片（*.jpg);;BMP图片（*.bmp)"));
    if (filename.isEmpty())
    {
        qDebug() << "Save filename is empty, cancel save.";
        return;
    }
#if 1
    // 检查并将之补全后缀名
    QFileInfo fileInfo(filename);
    if (fileInfo.suffix().isEmpty())
    {
        // 如果用户没有加后缀，默认加上.png
        filename += ".png";
    }
    // 使用局部保存变量 QByteArray，防止指针悬空
    QByteArray ba = filename.toUtf8();

#endif

    // 调用控制器，将平台相关的 QString 转换为统一的 const char*
    //    if(c->Save(filename.toLocal8Bit()))
    if (c->Save(ba.data()))
    {
        qDebug() << "Image saved successfully to:" << filename;
    }
    else
    {
        qDebug() << "Failed to save image!";
    }
}
// 鼠标重载函数
void XImage::mousePressEvent(QMouseEvent* e)
{
    // XEditView::getInstance().poss.push_back(XPos(e->x(), e->y()));
    // m.Add( XPos(e->x(), e->y()) );

    c->AddModel();
    c->SetPara("size", penSize);
    c->SetPara("r", r);
    c->SetPara("g", g);
    c->SetPara("b", b);
    c->SetPara("a", a);
    // c->Add(e->x(), e->y());
    c->Add(e->position().x(), e->position().y());
}
// 默认鼠标移动事件，按下才触发
void XImage::mouseMoveEvent(QMouseEvent* e)
{
    // XEditView::getInstance().poss.push_back(XPos(e->x(), e->y()));
    // m.Add(XPos(e->x(), e->y()));

    // c->AddModel();
    // c->Add(e->x(), e->y());
    c->Add(e->position().x(), e->position().y());
    update();
}

void XImage::mouseReleaseEvent(QMouseEvent* e)
{
    // 告诉控制器：这一笔画完了，固化图层
    c->FinishModel();
    // 触发最后一次UI刷新
    update();
}

void XImage::paintEvent(QPaintEvent* e)
{
    c->Paint();
    // XEditView::getInstance().Paint();

#if 0
    //绘制图片
    QPainter p(this);
    p.drawImage(0, 0, src);
#endif
}

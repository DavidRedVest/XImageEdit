#include "ximage.h"
#include <QDebug>
#include <QFileDialog>
#include <QPainter>

#include <QMouseEvent>
//#include "xeditview.h"
#include "xmodel.h"

#include "icontroller.h"
#include "xcontrollerfactory.h"

//XModel m;

XImage::XImage(QWidget *p):QWidget(p)
{
    c = IController::Create(new XControllerFactory());
    c->Init(this);

    //XEditView::getInstance().InitDevice(this);
    //视图观察模型
    //m.Attach(&XEditView::getInstance());
}


XImage::~XImage()
{
}

void XImage::Open()
{
   // qDebug() << "XImage::Open()" ;

    //打开图片
    QString filename = QFileDialog::getOpenFileName(this, QStringLiteral("打开图片"), "",
                                                    QStringLiteral("支持的格式(*.png *.jpg *.bmp)"));
    if(filename.isEmpty()) {
        qDebug()<<"Open filename is empty!";
        return;
    }
    //加载图片
    //if(!src.load(filename)) {
    //if(!XEditView::getInstance().InitBack(filename.toLocal8Bit())) {
    if(!c->InitBack(filename.toLocal8Bit())) {
        qDebug()<<"src.load image failed!";
        return;
    }
    //qDebug()<<"src.load image successful!";

    //显示通知，刷新滚动条布局
    if(this->parentWidget()) {
        this->parentWidget()->update();
    }

    //刷新显示
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
    //刷新显示
    update();

}
void XImage::Redo()
{
    c->Redo();
    //刷新显示
    update();

}
void XImage::SetPenSize(int size)
{
    penSize = size;
}


//鼠标重载函数
void XImage::mousePressEvent(QMouseEvent *e)
{
    //XEditView::getInstance().poss.push_back(XPos(e->x(), e->y()));
    //m.Add( XPos(e->x(), e->y()) );

    c->AddModel();
    c->SetPara("size", penSize);
    c->SetPara("r", r);
    c->SetPara("g", g);
    c->SetPara("b", b);
    c->SetPara("a", a);
    //c->Add(e->x(), e->y());
    c->Add(e->position().x(), e->position().y());
}
//默认鼠标移动事件，按下才触发
void XImage::mouseMoveEvent(QMouseEvent *e)
{
    //XEditView::getInstance().poss.push_back(XPos(e->x(), e->y()));
    //m.Add(XPos(e->x(), e->y()));

    //c->AddModel();
    //c->Add(e->x(), e->y());
    c->Add(e->position().x(), e->position().y());
    update();
}

void XImage::paintEvent(QPaintEvent *e)
{
    c->Paint();
    //XEditView::getInstance().Paint();

#if 0
    //绘制图片
    QPainter p(this);
    p.drawImage(0, 0, src);
#endif
}

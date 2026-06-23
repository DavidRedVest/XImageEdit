#include "xeditview.h"

#include <QPainter>
#include <QWidget>
#include "xmodel.h"

#include "xpengraph.h"
//XPenGraph xpen;

XEditView::XEditView()
{
    //初始化图像，未打开图像，直接画像
    out = QImage(1280, 720, QImage::Format_RGB888);
    out.fill(Qt::white);    //初始化为白色背景，默认是黑色
    src = QImage(1280, 720, QImage::Format_RGB888);
    //src.fill(Qt::white);
}
XEditView::~XEditView()
{

}

void XEditView::Update(XSubject *data)
{
    if(!data) {
        return;
    }

    XModel *m = static_cast<XModel *>(data);
    //通过类型判断
    auto it = views.find(m->type);
    if(it != views.end()) {
        //防止出现空的情况，以防程序崩溃
        views[m->type]->Draw(m);
    }
    
#if 0
    //使用容器初始化
    std::map<int, IGraph*>::iterator itr = views.begin();

    for(; itr != views.end(); itr++)
    {
        itr->second->Draw(m);
    }
#endif
    //xpen.Draw(m);

#if 0
    int size = m->poss.size();
    QPainter p(&out);
    for(int i = 1; i < size; ++i) {
        //绘制线，开始点到结束点
        p.drawLine(QLine(m->poss[i - 1].x, m->poss[i - 1].y, m->poss[i].x, m->poss[i].y));
    }
#endif
}

//显示目标
void XEditView::InitDevice(void *d)
{
    this->device = (QWidget *)d;
    if(!op) {
        op = new QPainter(&out);
    }

    //让外部的XImage控件大小直接等于当前画布大小
    if(device) {
        device->resize(out.size());
    }

    //上一次的清理掉
    op->end();
    op->begin(&out);

    //使用容器初始化
    std::map<int, IGraph*>::iterator itr = views.begin();
    for(; itr != views.end(); itr++)
    {
        itr->second->Init(op,&src);
    }
    //xpen.Init(op, &src);
}

//载入背景图
bool XEditView::InitBack(const char* url)
{
    //载入图片
    if(!src.load(QString::fromLocal8Bit(url))) {
        return false;
    }
    if(op->isActive()) {
        op->end();
    }
    out = src.copy();

    //图片载入成功后，动态调整XImage控件的大小为图片的实际宽高
    if(device) {
        device->resize(src.size());
    }

    op->begin(&out);
    return true;
}

//绘制结果
void XEditView::Paint()
{
    //在device窗口绘制
    QPainter p(device);

    p.drawImage(0, 0, out);
#if 0
    //绘制图片
    p.drawImage(0, 0, src);

    //绘制线条
    //所有坐标的数量
    int size = poss.size();
    //从1开始，画线要两个点
    for(int i = 1; i < size; ++i)
    {
        p.drawLine(QLine(poss[i-1].x, poss[i-1].y, poss[i].x, poss[i].y));
    }
#endif

}

//保存图片
//将带有绘制效果的out图像保存到指定路径
bool XEditView::Save(const char *url)
{
    if(out.isNull()) {
        qDebug() << "XEditView: out 图像为空，没有数据可以保存！";
        return false;
    }
    //Qt的QImage自带根据后缀名（png/jpg/bmp)自动编码保存的功能
//    return out.save(QString::fromLocal8Bit(url));

    // 对应前面的 toUtf8()，这里使用 fromUtf8() 解码
    QString savePath = QString::fromUtf8(url);

    // 调用 Qt 底层保存接口，quality 参数默认 -1
    bool success = out.save(savePath);

    if (!success) {
        qDebug() << "XEditView: QImage::save 底层调用失败，请检查路径权限或格式。路径：" << savePath;
    }

    return success;
}

#ifndef XEDITVIEW_H
#define XEDITVIEW_H

#include <QImage>
#include <vector>

#include "iview.h"

using namespace  std;

class QWidget;



//class XEditView :public IObserver
class XEditView :public IView
{
public:
    static XEditView &getInstance()
    {
        //C++11 标准保证了局部静态变量的初始化时线程安全的
        static XEditView v;
        return v;
    }

    //刷新到out中，在由paint更新
    virtual void Update(XSubject *data);

    //显示目标
    virtual void InitDevice(void *d);

    //载入背景图
    virtual bool InitBack(const char *url);

    //绘制结果
    virtual void Paint();

    ~XEditView();


protected:
    XEditView();
    QWidget *device;
     //原图
    QImage src;
    //输出图
    QImage out;
};

#endif // XEDITVIEW_H

#ifndef XEDITVIEW_H
#define XEDITVIEW_H

#include <QImage>
#include <vector>
#include <map>

#include "iview.h"

//using namespace  std;

class QWidget;
class IGraph;


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

    //保存接口
    virtual bool Save(const char *url) override;

    template<class ViewClass>
    IGraph* RegView(int type)
    {
        ViewClass *view = new ViewClass();
        views.insert(std::make_pair(type, view));
        return view;
    }

    ~XEditView();


protected:
    XEditView();

    //图元编号 外部维护
    std::map<int, IGraph*> views;

    QWidget *device;
     //原图
    QImage src;
    //输出图
    QImage out;

    //绘制到out
    QPainter *op = 0;
};

#endif // XEDITVIEW_H

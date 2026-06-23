#ifndef IVIEW_H
#define IVIEW_H

#include "iobserver.h"

class IView : public IObserver
{
public:
    //显示目标
    virtual void InitDevice(void *d) = 0;

    //载入背景图
    virtual bool InitBack(const char *url) = 0;

    //绘制结果
    virtual void Paint() = 0;

    //保存图片接口
    virtual bool Save(const char *url) = 0;

};

#endif // IVIEW_H

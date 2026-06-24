#ifndef IVIEW_H
#define IVIEW_H

#include "iobserver.h"

class IView : public IObserver
{
   public:
    // 显示目标
    virtual void InitDevice(void* d) = 0;

    // 载入背景图
    virtual bool InitBack(const char* url) = 0;

    // 绘制结果
    virtual void Paint() = 0;

    // 保存图片接口
    virtual bool Save(const char* url) = 0;

    // 增加双缓冲控制接口
    virtual void Commit() = 0;  // 将临时绘制固化到底图
    virtual void Clear() = 0;   // 清空底图，恢复为原始图片
};

#endif  // IVIEW_H

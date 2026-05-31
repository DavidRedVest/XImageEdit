#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include "icontrollerfactory.h"
#include <vector>

enum XSTATUS
{
    XPEN,
    XERASER
};

class IController
{
public:

    static IController* Create(IControllerFactory *f);

    virtual void Init(void *device);
    virtual bool InitBack(const char *url);
    //添加模型对象
    virtual void AddModel();
    //给当前模型添加数据
    virtual void Add(int x, int y);
    virtual void Paint();

    IController();
protected:
    IView *v = 0;
    XModel *m = 0;
    IControllerFactory *f = 0;
    //命令队列
    std::vector<XModel*> tasks;
};

#endif // ICONTROLLER_H

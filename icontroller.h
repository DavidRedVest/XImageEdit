#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include "icontrollerfactory.h"
#include <vector>

enum XSTATUS
{
    XPEN,
    XERASER,
    XRECT,
    XIMAGE
};

class IController
{
public:

    static IController* Create(IControllerFactory *f);

    virtual void Init(void *device);
    virtual bool InitBack(const char *url);
    //添加模型对象,-1表示当前状态
    virtual void AddModel(int s = -1);
    //给当前模型添加数据
    virtual void Add(int x, int y);
    virtual void Paint();
    virtual void SetStatus(XSTATUS s) {status = s;}
    virtual void NotfyAll();
    virtual void Undo();
    virtual void Redo();

    IController();
protected:
    IView *v = 0;
    XModel *m = 0;
    IControllerFactory *f = 0;
    //命令队列
    std::vector<XModel*> tasks;
    std::vector<XModel*> retasks;

    XSTATUS status = XPEN;
};

#endif // ICONTROLLER_H

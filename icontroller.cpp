#include "icontroller.h"
#include "iview.h"
#include "xmodel.h"

IController::IController() {}


IController* IController::Create(IControllerFactory *f)
{
    if(!f) {
        return 0;
    }
    IController* c = f->CreateC();
    //c->m = f->CreateM();
    c->v = f->CreateV();
    c->f = f;

    return c;
}

void IController::Init(void *device)
{
    //添加背景图
    AddModel(XIMAGE);
    v->InitDevice(device);
}

bool IController::InitBack(const char *url)
{
    bool re = v->InitBack(url);
    //添加背景图
    AddModel(XIMAGE);
    return re;
}

void IController::AddModel(int s)
{
    if(s<0) s = status;
    //创建模型
    m = f->CreateM();
    //添加观察者
    m->Attach(v);
    m->type = s;
    tasks.push_back(m);
}

void IController::Add(int x, int y)
{
    if(!m) {
        return;
    }
    m->Add(XPos(x, y));
    NotfyAll();
}

void IController::Paint()
{
    v->Paint();
}
void IController::NotfyAll()
{
    int size = tasks.size();
    for(int i = 0; i < size; ++i)
    {
        tasks[i]->Notify();
    }
}

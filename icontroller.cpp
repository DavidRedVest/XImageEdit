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
    v->InitDevice(device);
}

bool IController::InitBack(const char *url)
{
    return v->InitBack(url);
}

void IController::AddModel()
{
    //创建模型
    m = f->CreateM();
    //添加观察者
    m->Attach(v);
    m->type = status;
    tasks.push_back(m);
}

void IController::Add(int x, int y)
{
    if(!m) {
        return;
    }
    m->Add(XPos(x, y));
}

void IController::Paint()
{
    v->Paint();
}

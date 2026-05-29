#include "icontroller.h"
#include "iview.h"

IController::IController() {}


IController* IController::Create(IControllerFactory *f)
{
    if(!f) {
        return 0;
    }
    IController* c = f->CreateC();
    c->m = f->CreateM();
    c->v = f->CreateV();

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

void IController::Paint()
{
    v->Paint();
}

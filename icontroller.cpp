#include "icontroller.h"

IController::IController() {}


IController* IController::Create(IControllerFactory *f)
{
    if(!f) {
        return 0;
    }
    IController* c = f->CreateC();
    c->m = f->CreateM();
    c->v = f->CreateV();
}

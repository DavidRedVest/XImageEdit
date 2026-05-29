#ifndef ICONTROLLER_H
#define ICONTROLLER_H
#include "icontrollerfactory.h"
class IController
{
public:

    static IController* Create(IControllerFactory *f);

    virtual void Init(void *device);
    virtual bool InitBack(const char *url);
    virtual void Paint();

    IController();
protected:
    IView *v = 0;
    XModel *m = 0;
};

#endif // ICONTROLLER_H

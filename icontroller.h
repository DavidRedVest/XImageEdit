#ifndef ICONTROLLER_H
#define ICONTROLLER_H
#include "icontrollerfactory.h"
class IController
{
public:

    static IController* Create(IControllerFactory *f);

    IController();
protected:
    IView *v = 0;
    XModel *m = 0;
};

#endif // ICONTROLLER_H

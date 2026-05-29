#ifndef XCONTROLLERFACTORY_H
#define XCONTROLLERFACTORY_H

#include "icontrollerfactory.h"

class XControllerFactory : public IControllerFactory
{
public:
    XControllerFactory();

    static XControllerFactory &getInstance()
    {
        static XControllerFactory f;
        return f;
    }

    virtual XModel *CreateM();
    virtual IView *CreateV();
    virtual IController *CreateC();
};

#endif // XCONTROLLERFACTORY_H

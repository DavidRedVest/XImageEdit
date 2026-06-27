#ifndef XCONTROLLERFACTORY_H
#define XCONTROLLERFACTORY_H

#include "icontrollerfactory.h"

class XControllerFactory : public IControllerFactory {
   public:
    XControllerFactory();

    static XControllerFactory& getInstance() {
        static XControllerFactory f;
        return f;
    }

    XModel* CreateM() override;
    IView* CreateV() override;
    IController* CreateC() override;
};

#endif  // XCONTROLLERFACTORY_H

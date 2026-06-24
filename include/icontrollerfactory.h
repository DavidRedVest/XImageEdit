#ifndef ICONTROLLERFACTORY_H
#define ICONTROLLERFACTORY_H

class IController;
class XModel;
class IView;

class IControllerFactory
{
   public:
    virtual XModel* CreateM() = 0;
    virtual IView* CreateV() = 0;
    virtual IController* CreateC() = 0;
};

#endif  // ICONTROLLERFACTORY_H

#include "xcontrollerfactory.h"
#include "xmodel.h"
#include "icontroller.h"
#include "xeditview.h"


XControllerFactory::XControllerFactory()
{
    //构造函数
}

XModel* XControllerFactory::CreateM()
{
    return new XModel();
}
IView* XControllerFactory::CreateV()
{
    return &(XEditView::getInstance());
}
IController* XControllerFactory::CreateC()
{
    return new IController();
}

#include "xcontrollerfactory.h"
#include "xmodel.h"
#include "icontroller.h"
#include "xeditview.h"
#include "xpengraph.h"

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
    XEditView::getInstance().RegView<XPenGraph>(XPEN);
    return &(XEditView::getInstance());
}
IController* XControllerFactory::CreateC()
{
    return new IController();
}

#include "xcontrollerfactory.h"
#include "xmodel.h"
#include "icontroller.h"
#include "xeditview.h"
#include "xpengraph.h"
#include "xerasegraph.h"

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
    XEditView::getInstance().RegView<XEraseGraph>(XERASER);
    return &(XEditView::getInstance());
}
IController* XControllerFactory::CreateC()
{
    return new IController();
}

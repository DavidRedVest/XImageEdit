#include "xcontrollerfactory.h"

#include "icontroller.h"
#include "xeditview.h"
#include "xerasegraph.h"
#include "ximagegraph.h"
#include "xmodel.h"
#include "xpengraph.h"
#include "xrectgraph.h"

XControllerFactory::XControllerFactory() {
    // 构造函数
}

XModel* XControllerFactory::CreateM() {
    return new XModel();
}
IView* XControllerFactory::CreateV() {
    return &(XEditView::getInstance());
}
IController* XControllerFactory::CreateC() {
    return new IController();
}

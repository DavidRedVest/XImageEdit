#include "xmodel.h"

XModel::XModel()
{

}

XModel::~XModel()
{

}


void XModel::Add(XPos pos)
{
    this->poss.push_back(pos);

    //通知观察者
    this->Notify();
}

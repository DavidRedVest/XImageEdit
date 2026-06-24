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

    // 通知观察者
    // this->Notify();   //写了一个通知所有模块的函数，就不需要单独通知了
}

void XModel::SetPara(std::string key, int val)
{
    // 没有就添加
    if (paras.find(key) == paras.end())
    {
        paras.insert(make_pair(key, val));
    }
    else
    {
        // 如果有值就修改
        paras[key] = val;
    }
}
int XModel::GetPara(std::string key)
{
    // 没有
    if (paras.find(key) == paras.end())
    {
        return 0;
    }
    return paras[key];
}

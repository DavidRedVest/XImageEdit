#include "xmodel.h"

XModel::XModel() {
}

XModel::~XModel() {
}

void XModel::Add(XPos pos) {
    this->poss.push_back(pos);

    // 通知观察者
    // this->Notify();   //写了一个通知所有模块的函数，就不需要单独通知了
}

void XModel::SetPara(const std::string& key, int val) {
    paras[key] = val;
}
int XModel::GetPara(const std::string& key) {
    // 没有
    if (paras.find(key) == paras.end()) {
        return 0;
    }
    return paras[key];
}

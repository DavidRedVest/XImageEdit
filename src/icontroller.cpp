#include "icontroller.h"

#include "iview.h"
#include "xmodel.h"

IController::IController() {
}

IController* IController::Create(IControllerFactory* f) {
    if (!f) {
        return 0;
    }
    IController* c = f->CreateC();
    if (!c) {
        return 0;
    }
    // c->m = f->CreateM();
    c->v = f->CreateV();
    c->f = f;

    return c;
}

void IController::Init(void* device) {
    if (v) {
        v->InitDevice(device);
    }
}

bool IController::InitBack(const char* url) {
    if (!v) {
        return false;
    }
    bool re = v->InitBack(url);
    if (re) {
        ClearHistory();
    }
    return re;
}

void IController::AddModel(int s) {
    if (!f || !v) {
        return;
    }
    if (s < 0) {
        s = status;
    }
    // 创建模型
    // m = f->CreateM();
    // 使用shared_ptr结果工厂返回的裸指针
    m = std::shared_ptr<XModel>(f->CreateM());
    if (!m) {
        return;
    }

    // 添加观察者
    m->Attach(v);
    m->type = s;
    tasks.push_back(m);
    retasks.clear();
}

void IController::Add(int x, int y) {
    if (!m) {
        return;
    }
    m->Add(XPos(x, y));
    NotfyAll();  // 只触发当前模型更新，画在临时层上
}

void IController::FinishModel() {
    if (v) {
        v->Commit();
    }
    m.reset();
}
void IController::Paint() {
    if (v) {
        v->Paint();
    }
}
void IController::NotfyAll() {
    if (!v) {
        return;
    }

    // 彻底清空画布到背景图
    v->Clear();

    // 按照历史记录，把剩下的任务重新“重播”一遍
    for (const auto& task : tasks) {
        task->Notify();  // 画在临时层上
        v->Commit();     // 立即固化在底层图上
    }
}
// 撤消
void IController::Undo() {
    if (tasks.empty()) {
        return;
    }
    retasks.push_back(tasks.back());
    tasks.pop_back();
    NotfyAll();
}
// 恢复
void IController::Redo() {
    if (retasks.empty()) {
        return;
    }
    tasks.push_back(retasks.back());
    retasks.pop_back();
    NotfyAll();
}

void IController::SetPara(const std::string& key, int val) {
    if (!m) {
        return;
    }
    m->SetPara(key, val);
}

// 委托给试图指针v执行保存
bool IController::Save(const char* url) {
    if (!v) {
        return false;
    }
    return v->Save(url);
}

void IController::ClearHistory() {
    tasks.clear();
    retasks.clear();
    m.reset();
}

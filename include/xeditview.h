#ifndef XEDITVIEW_H
#define XEDITVIEW_H

#include <QImage>
#include <map>
#include <memory>
#include <vector>

#include "iview.h"

class QWidget;
class IGraph;

// class XEditView :public IObserver
class XEditView : public IView {
   public:
    static XEditView& getInstance() {
        // C++11 标准保证了局部静态变量的初始化时线程安全的
        static XEditView v;
        return v;
    }

    // 刷新到out中，在由paint更新
    virtual void Update(XSubject* data);

    // 显示目标
    virtual void InitDevice(void* d);

    // 载入背景图
    virtual bool InitBack(const char* url);

    // 绘制结果
    virtual void Paint();

    // 保存接口
    virtual bool Save(const char* url) override;

    template <class ViewClass>
    IGraph* RegView(int type) {
        auto view = std::make_unique<ViewClass>();
        IGraph* rawView = view.get();
        views[type] = std::move(view);
        return rawView;
    }

    ~XEditView();

    virtual void Commit() override;
    virtual void Clear() override;

   private:
    // 重制输出层并立即重新绑定画家，同时通知所有IGraph
    // 凡是要给out赋新值，必须且只能通过这个函数
    void resetOutLayer(const QImage& source);

   protected:
    XEditView();

    // 图元编号 外部维护
    std::map<int, std::unique_ptr<IGraph>> views;

    QWidget* device = nullptr;
    // 原图
    QImage src;
    // 输出图
    QImage out;

    // 绘制到out
    QPainter* op = nullptr;

    QImage baseLayer;  // 底图层，保存已固定的历史操作
};

#endif  // XEDITVIEW_H

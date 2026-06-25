#include "xeditview.h"

#include <QPainter>
#include <QWidget>

#include "xmodel.h"
#include "xpengraph.h"
// XPenGraph xpen;
#include "constants.h"
#include "icontroller.h"
#include "xerasegraph.h"
#include "ximagegraph.h"
#include "xrectgraph.h"

XEditView::XEditView() {
    // 初始化图像，未打开图像，直接画像
    out = QImage(AppConfig::DEFAULT_CANVAS_WIDTH,
                 AppConfig::DEFAULT_CANVAS_HEIGHT, QImage::Format_RGB888);
    out.fill(Qt::white);  // 初始化为白色背景，默认是黑色
    src = QImage(AppConfig::DEFAULT_CANVAS_WIDTH,
                 AppConfig::DEFAULT_CANVAS_HEIGHT, QImage::Format_RGB888);
    // src.fill(Qt::white);

    // 只创建一次
    views[XPEN] = new XPenGraph();
    views[XERASER] = new XEraseGraph();
    views[XRECT] = new XRectGraph();
    views[XIMAGE] = new XImageGraph();
}
XEditView::~XEditView() {
    if (op) {
        if (op->isActive()) {
            op->end();
        }
        delete op;
        op = nullptr;
    }
    for (auto& [type, graph] : views) {
        delete graph;
    }
}

// 双缓冲核心逻辑：每次鼠标移动重绘时调用
void XEditView::Update(XSubject* data) {
    if (!data) {
        return;
    }

    XModel* m = static_cast<XModel*>(data);

    resetOutLayer(baseLayer);
    // 在刚绑定好的op上绘制当前画笔
    auto it = views.find(m->type);
    if (it != views.end()) {
        it->second->Draw(m);
    }
}

// 显示目标
void XEditView::InitDevice(void* d) {
    this->device = static_cast<QWidget*>(d);
    if (device) {
        device->setFixedSize(out.size());
    }
    // out内容不变，只是首次绑定op
    resetOutLayer(out);
}

// 载入背景图
bool XEditView::InitBack(const char* url) {
    // 载入图片
    if (!src.load(QString::fromLocal8Bit(url))) {
        return false;
    }
    baseLayer = src.copy();
    // out换新，必须经过resetOutLayer,op同步更新
    resetOutLayer(baseLayer);
    if (device) {
        device->setFixedSize(src.size());
    }
    return true;

    return true;
}

// 绘制结果
void XEditView::Paint() {
    // 在device窗口绘制
    QPainter p(device);
    p.drawImage(0, 0, out);
}

// 保存图片
// 将带有绘制效果的out图像保存到指定路径
bool XEditView::Save(const char* url) {
    if (out.isNull()) {
        qDebug() << "XEditView: out 图像为空，没有数据可以保存！";
        return false;
    }

    // 对应前面的 toUtf8()，这里使用 fromUtf8() 解码
    QString savePath = QString::fromUtf8(url);

    // 调用 Qt 底层保存接口，quality 参数默认 -1
    bool success = out.save(savePath);

    if (!success) {
        qDebug() << "XEditView: QImage::save "
                    "底层调用失败，请检查路径权限或格式。路径："
                 << savePath;
    }
    return success;
}

// 清空所有绘制，恢复为原图
void XEditView::Clear() {
    baseLayer = src.copy();
    resetOutLayer(baseLayer);
}

// 将鼠标松开时的最终画面固化到基础层
void XEditView::Commit() {
    //    baseLayer = out.copy();

    // op必须先关闭，否则QPainter还持有out的写锁
    // copy()在有活跃QPainter时行为未定义
    if (op && op->isActive()) {
        op->end();
    }
    baseLayer = out.copy();
    // commit之后马上重新开启op,保持op始终active的不变式
    op->begin(&out);
    for (auto& [type, graph] : views) {
        graph->Init(op, &src);
    }
}

void XEditView::resetOutLayer(const QImage& source) {
    // 先安全结束当前画家
    if (op && op->isActive()) {
        op->end();
    }
    // 给out赋新值（像素内存在这里被替换）
    out = source.copy();

    // 立刻重新绑定op到新内存
    // 关键步骤：紧跟赋值，不允许分离
    if (!op) {
        op = new QPainter();  // 延迟构造，不再构造函数里面
    }
    op->begin(&out);

    // 通知所有IGraph更新画家指针
    for (auto& [type, graph] : views) {
        graph->Init(op, &src);
    }
}
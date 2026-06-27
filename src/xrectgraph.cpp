#include "xrectgraph.h"

#include <QPainter>
#include <QPen>
#include <algorithm>

#include "constants.h"
#include "xmodel.h"

void XRectGraph::Draw(XModel* m) {
    if (!painter || !m) {
        return;
    }
    QPen pen;  // 画笔
    pen.setWidth(std::max(AppConfig::MIN_PEN_SIZE,
                          m->GetPara("size", AppConfig::DEFAULT_PEN_SIZE)));
    // pen.setColor(QColor(200, 0, 0));
    pen.setColor(QColor(m->GetPara("r", AppConfig::DEFAULT_COLOR_R),
                        m->GetPara("g", AppConfig::DEFAULT_COLOR_G),
                        m->GetPara("b", AppConfig::DEFAULT_COLOR_B),
                        m->GetPara("a", AppConfig::DEFAULT_COLOR_A)));
    // 设置连接处
    pen.setCapStyle(Qt::RoundCap);    // 顶部样式
    pen.setJoinStyle(Qt::RoundJoin);  // 连接处样式

    // 设置抗锯齿
    painter->setRenderHint(QPainter::Antialiasing, true);  // 顶部样式
    painter->setPen(pen);
    int size = m->poss.size();
    if (size < 2) {
        return;
    }
    int x = m->poss[0].x;
    int y = m->poss[0].y;
    int w = m->poss[size - 1].x - x;
    int h = m->poss[size - 1].y - y;
    // 从起始点到结尾画矩形
    painter->drawRect(x, y, w, h);
}

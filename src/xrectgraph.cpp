#include "xrectgraph.h"

#include <QPainter>
#include <QPen>

#include "xmodel.h"

void XRectGraph::Draw(XModel* m)
{
    if (!painter || !m)
    {
        return;
    }
    QPen pen;                          // 画笔
    pen.setWidth(m->GetPara("size"));  // 设置画笔线条宽度
    // pen.setColor(QColor(200, 0, 0));
    pen.setColor(QColor(m->GetPara("r"), m->GetPara("g"), m->GetPara("b"),
                        m->GetPara("a")));
    // 设置连接处
    pen.setCapStyle(Qt::RoundCap);    // 顶部样式
    pen.setJoinStyle(Qt::RoundJoin);  // 连接处样式

    // 设置抗锯齿
    painter->setRenderHint(QPainter::Antialiasing, true);  // 顶部样式
    painter->setPen(pen);
    int size = m->poss.size();
    if (size < 2)
    {
        return;
    }
    int x = m->poss[0].x;
    int y = m->poss[0].y;
    int w = m->poss[size - 1].x - x;
    int h = m->poss[size - 1].y - y;
    // 从起始点到结尾画矩形
    painter->drawRect(x, y, w, h);

#if 0
    for(int i = 1; i < size; ++i) {
        //绘制线，开始点到结束点
        painter->drawLine(QLine(m->poss[i - 1].x, m->poss[i - 1].y, m->poss[i].x, m->poss[i].y));
    }
#endif
}

#ifndef IGRAPH_H
#define IGRAPH_H

class QPainter;
class QImage;
class XModel;


class IGraph
{
public:
    virtual void Init(QPainter *p, QImage *s)
    {
        painter = p;
        src = s;
    }
    //绘制图元
    virtual void Draw(XModel *m) = 0;
protected:
    QPainter *painter = 0;
    //原图、背景图
    QImage *src = 0;
};

#endif // IGRAPH_H

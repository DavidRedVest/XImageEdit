#ifndef XMODEL_H
#define XMODEL_H

#include "xsubject.h"
#include <vector>

struct XPos
{
    XPos(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    int x = 0;
    int y = 0;
};

class XModel : public XSubject
{
public:
    //点坐标
    std::vector <XPos> poss;

    void Add(XPos pos);

    XModel();
    ~XModel();
};

#endif // XMODEL_H

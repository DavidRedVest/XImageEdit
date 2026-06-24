#ifndef XPENGRAPH_H
#define XPENGRAPH_H

#include "igraph.h"

class XPenGraph : public IGraph
{
   public:
    virtual void Draw(XModel* m);
};

#endif  // XPENGRAPH_H

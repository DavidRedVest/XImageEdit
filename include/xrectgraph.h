#ifndef XRECTGRAPH_H
#define XRECTGRAPH_H

#include "igraph.h"

class XRectGraph : public IGraph
{
   public:
    virtual void Draw(XModel* m);
};

#endif  // XRECTGRAPH_H

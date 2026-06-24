#ifndef XIMAGEGRAPH_H
#define XIMAGEGRAPH_H

#include "igraph.h"

class XImageGraph : public IGraph
{
   public:
    virtual void Draw(XModel* m);
};

#endif  // XIMAGEGRAPH_H

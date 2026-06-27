#ifndef XRECTGRAPH_H
#define XRECTGRAPH_H

#include "igraph.h"

class XRectGraph : public IGraph {
   public:
    void Draw(XModel* m) override;
};

#endif  // XRECTGRAPH_H

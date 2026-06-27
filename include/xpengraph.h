#ifndef XPENGRAPH_H
#define XPENGRAPH_H

#include "igraph.h"

class XPenGraph : public IGraph {
   public:
    void Draw(XModel* m) override;
};

#endif  // XPENGRAPH_H

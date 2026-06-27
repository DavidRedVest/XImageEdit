#ifndef XIMAGEGRAPH_H
#define XIMAGEGRAPH_H

#include "igraph.h"

class XImageGraph : public IGraph {
   public:
    void Draw(XModel* m) override;
};

#endif  // XIMAGEGRAPH_H

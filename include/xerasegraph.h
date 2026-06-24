#ifndef XERASEGRAPH_H
#define XERASEGRAPH_H

#include "igraph.h"

class XEraseGraph : public IGraph
{
   public:
    void Draw(XModel* m);
};

#endif  // XERASEGRAPH_H

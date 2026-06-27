#include "ximagegraph.h"

#include <QPainter>

void XImageGraph::Draw(XModel* m) {
    if (!painter || !src || src->isNull() || !m) {
        return;
    }
    painter->drawImage(0, 0, *src);
}

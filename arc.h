#ifndef ARC_H
#define ARC_H

#include "node.h"
class Arc
{
    Node firstNode, secondNode;
public:
    Arc(Node n1, Node n2);
    Node getFirstPoint();
    Node getSecondPoint();
};
#endif // ARC_H

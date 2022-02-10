#include "arc.h"

Arc::Arc(Node n1, Node n2)
{
    firstNode = n1;
    secondNode = n2;
}

Node Arc::getFirstPoint()
{
    return firstNode;
}
Node Arc::getSecondPoint()
{
    return secondNode;
}

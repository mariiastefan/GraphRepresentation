#ifndef NODE_H
#define NODE_H

#include <QPainter>

class Node
{
    QPoint point;
    int number;

public:
    Node(){ number = -1; };
    Node(QPoint p){
        point = p;
    }
    QPoint getPoint() {
        return point;
    }
    int getNumber() {
        return number;
    }
    void setNumber(int number) {
        this->number = number;
    }


};

#endif // NODE_H

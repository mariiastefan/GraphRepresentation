#ifndef GRAF_H
#define GRAF_H

#include "node.h"
#include "arc.h"
#include <QMatrix>
class Graf
{
    std::vector<Node> noduri;
    std::vector<Arc> arce;
    int **matriceAD;
    std::vector<std::vector<int>> matriceAdiacenta;
    std::vector<Arc> listaAdiacenta;
public:
    void GenerareMatriceAdiacenta();
    void GenerareListaAdiacenta();
    std::vector<Arc> GetArce();
    std::vector<Node> GetNoduri();
    bool Add(Node n);
    void AddNod(Node n);
    void AddArc(Arc a);
    void DrawGraf(QPainter *p);
    Node GetLastNode();
    int getNumberofNodes();
    void gasireaRadacinii();
    void Graf::DFS(int x, std::vector<int> &visited);
};
#endif // GRAF_H

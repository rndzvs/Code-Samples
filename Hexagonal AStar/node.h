#include "point.h"

class Node {
public:
    const Point tilePos; // cell coordinates
    float f = 0.0;
    float g = 0.0;
    float h = 0.0;
    Node* parent = NULL;

    Node(Point pos, float f_, float g_, float h_, Node* p) : tilePos(pos), f(f_), g(g_), h(h_), parent(p) {};
    Node(Node &n) : tilePos(n.tilePos), f(n.f), g(n.g), h(n.h), parent(n.parent) {};
};

bool sortNodeF(Node &n1, Node &n2) { return n1.f < n2.f; }
bool sortNodeFPointer(Node* n1, Node* n2) { return sortNodeF(*n1,*n2); }
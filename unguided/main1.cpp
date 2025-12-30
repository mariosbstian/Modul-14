#include "graph1.h"
#include <iostream>
using namespace std;

int main() {
    Graph G;
    initGraph(G);

    addNode(G, 'A'); adrNode A = G.head;
    addNode(G, 'B'); adrNode B = A->next;
    addNode(G, 'C'); adrNode C = B->next;
    addNode(G, 'D'); adrNode D = C->next;
    addNode(G, 'E'); adrNode E = D->next;
    addNode(G, 'F'); adrNode F = E->next;
    addNode(G, 'G'); adrNode Gx = F->next;
    addNode(G, 'H'); adrNode H = Gx->next;

    linkNode(A, B);
    linkNode(A, C);
    linkNode(B, D);
    linkNode(B, E);
    linkNode(C, F);
    linkNode(C, Gx);
    linkNode(D, H);
    linkNode(E, H);
    linkNode(F, H);
    linkNode(Gx, H);

    cout << "=== LIST GRAPH ===" << endl;
    showGraph(G);
    cout << endl;

    return 0;
}

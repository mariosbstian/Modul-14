#include "graph2.h"
#include <iostream>

using namespace std;

int main() {
    Graph G;
    initGraph(G);

    addNode(G, 'A'); NodePtr A = G.head;
    addNode(G, 'B'); NodePtr B = A->next;
    addNode(G, 'C'); NodePtr C = B->next;
    addNode(G, 'D'); NodePtr D = C->next;
    addNode(G, 'E'); NodePtr E = D->next;
    addNode(G, 'F'); NodePtr F = E->next;
    addNode(G, 'G'); NodePtr G2 = F->next;
    addNode(G, 'H'); NodePtr H = G2->next;

    addConnection(A, B);
    addConnection(A, C);
    addConnection(B, D);
    addConnection(B, E);
    addConnection(C, F);
    addConnection(C, G2);
    addConnection(D, H);
    addConnection(E, H);
    addConnection(F, H);
    addConnection(G2, H);

    cout << "=== LIST GRAPH ===" << endl;
    showGraph(G);
    cout << endl;

    cout << "=== Hasil Traversal DFS ===" << endl;
    DFS(G, A);
}

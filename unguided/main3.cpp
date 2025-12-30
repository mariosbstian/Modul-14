#include "graph3.h"
#include <iostream>
using namespace std;

int main() {
    Graph G;
    initGraph(G);

    insertVertex(G, 'A'); NodeAdr A = G.first;
    insertVertex(G, 'B'); NodeAdr B = A->next;
    insertVertex(G, 'C'); NodeAdr C = B->next;
    insertVertex(G, 'D'); NodeAdr D = C->next;
    insertVertex(G, 'E'); NodeAdr E = D->next;
    insertVertex(G, 'F'); NodeAdr F = E->next;
    insertVertex(G, 'G'); NodeAdr G2 = F->next;
    insertVertex(G, 'H'); NodeAdr H = G2->next;

    connectVertex(A, B);
    connectVertex(A, C);
    connectVertex(B, D);
    connectVertex(B, E);
    connectVertex(C, F);
    connectVertex(C, G2);
    connectVertex(D, H);
    connectVertex(E, H);
    connectVertex(F, H);
    connectVertex(G2, H);

    cout << "=== LIST GRAPH ===" << endl;
    displayGraph(G);
    cout << endl;

    cout << "=== Hasil Traversal DFS ===" << endl;
    traversalDFS(G, A);
    cout << endl;

    cout << "=== Hasil Traversal BFS ===" << endl;
    traversalBFS(G, A);
    cout << endl;
}

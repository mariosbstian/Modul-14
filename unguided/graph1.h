#ifndef GRAPH1_H
#define GRAPH1_H

#include <iostream>
using namespace std;

typedef char infotype;
typedef struct Node *adrNode;
typedef struct Edge *adrEdge;

struct Edge {
    adrNode target;
    adrEdge next;
};

struct Node {
    infotype data;
    adrEdge edgeList;
    adrNode next;
};

struct Graph {
    adrNode head;
};

void initGraph(Graph &G);
void addNode(Graph &G, infotype x);
void linkNode(adrNode P, adrNode Q);
void showGraph(Graph &G);

#endif

#ifndef GRAPH2_H
#define GRAPH2_H

#include <iostream>
using namespace std;

typedef char InfoType;

typedef struct Edge *EdgePtr;
typedef struct Node *NodePtr;

struct Edge {
    NodePtr tujuan;
    EdgePtr next;
};

struct Node {
    InfoType data;
    bool visited;
    EdgePtr edgeList;
    NodePtr next;
};

struct Graph {
    NodePtr head;
};

void initGraph(Graph &G);
void addNode(Graph &G, InfoType x);
void addConnection(NodePtr a, NodePtr b);
void showGraph(Graph &G);
void DFS(Graph &G, NodePtr start);

#endif

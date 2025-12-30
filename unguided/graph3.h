#ifndef GRAPH3_H
#define GRAPH3_H

#include <iostream>
using namespace std;

typedef char DataType;

typedef struct EdgeNode *EdgeAdr;
typedef struct GraphNode *NodeAdr;

struct EdgeNode {
    NodeAdr link;
    EdgeAdr next;
};

struct GraphNode {
    DataType value;
    bool visited;
    EdgeAdr adj;
    NodeAdr next;
};

struct Graph {
    NodeAdr first;
};

void initGraph(Graph &G);
void insertVertex(Graph &G, DataType x);
void connectVertex(NodeAdr a, NodeAdr b);
void displayGraph(Graph &G);
void traversalDFS(Graph &G, NodeAdr start);
void traversalBFS(Graph &G, NodeAdr start);

#endif

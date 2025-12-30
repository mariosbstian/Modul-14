#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

using namespace std;

typedef char infoGraph;
typedef struct ElmNode *adrNode;
typedef struct ElmEdge *adrEdge;

struct ElmNode {
    infoGraph info;    
    int visited;       
    adrEdge firstEdge; 
    adrNode Next;      
};

struct ElmEdge {
    adrNode Node;  
    adrEdge Next;  
};

struct Graph {
    adrNode First; 
};

void CreateGraph(Graph &G);  
adrNode AlokasiNode(infoGraph data);  
adrEdge AlokasiEdge(adrNode nodeTujuan);  

void InsertNode(Graph &G, infoGraph data);  
adrNode FindNode(Graph G, infoGraph data);  
void ConnectNode(Graph &G, infoGraph info1, infoGraph info2); 
void DisconnectNode(adrNode node1, adrNode node2);  
void DeleteNode(Graph &G, infoGraph X);  

void PrintInfoGraph(Graph G);  
void ResetVisited(Graph &G);  
void PrintBFS(Graph G, infoGraph StartInfo);  
void PrintDFS(Graph G, infoGraph StartInfo);  

#endif
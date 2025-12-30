#include "graph1.h"

void initGraph(Graph &G) {
    G.head = NULL;
}

void addNode(Graph &G, infotype x) {
    adrNode newNode = new Node;
    newNode->data = x;
    newNode->edgeList = NULL;
    newNode->next = NULL;

    if (G.head == NULL) {
        G.head = newNode;
    } else {
        adrNode temp = G.head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void linkNode(adrNode P, adrNode Q) {
    if (P != NULL && Q != NULL) {
        adrEdge e1 = new Edge;
        e1->target = Q;
        e1->next = P->edgeList;
        P->edgeList = e1;

        adrEdge e2 = new Edge;
        e2->target = P;
        e2->next = Q->edgeList;
        Q->edgeList = e2;
    }
}

void showGraph(Graph &G) {
    adrNode node = G.head;
    while (node != NULL) {
        cout << "Node " << node->data << " terhubung ke: ";
        adrEdge edge = node->edgeList;
        while (edge != NULL) {
            cout << edge->target->data << " ";
            edge = edge->next;
        }
        cout << endl;
        node = node->next;
    }
}

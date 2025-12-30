#include "graph2.h"
#include <stack>

void initGraph(Graph &G) {
    G.head = NULL;
}

void addNode(Graph &G, InfoType x) {
    NodePtr newNode = new Node;
    newNode->data = x;
    newNode->visited = false;
    newNode->edgeList = NULL;
    newNode->next = NULL;

    if (G.head == NULL) {
        G.head = newNode;
    } else {
        NodePtr temp = G.head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void addConnection(NodePtr a, NodePtr b) {
    if (a == NULL || b == NULL) return;

    EdgePtr e1 = new Edge;
    e1->tujuan = b;
    e1->next = a->edgeList;
    a->edgeList = e1;

    EdgePtr e2 = new Edge;
    e2->tujuan = a;
    e2->next = b->edgeList;
    b->edgeList = e2;
}

void showGraph(Graph &G) {
    NodePtr n = G.head;
    while (n != NULL) {
        cout << "Node " << n->data << " terhubung ke: ";
        EdgePtr e = n->edgeList;
        while (e != NULL) {
            cout << e->tujuan->data << " ";
            e = e->next;
        }
        cout << endl;
        n = n->next;
    }
}

void DFS(Graph &G, NodePtr start) {
    if (start == NULL) return;

    stack<NodePtr> s;
    s.push(start);

    cout << "DFS Traversal: ";
    while (!s.empty()) {
        NodePtr curr = s.top();
        s.pop();

        if (!curr->visited) {
            curr->visited = true;
            cout << curr->data << " - ";

            EdgePtr e = curr->edgeList;
            while (e != NULL) {
                if (!e->tujuan->visited) {
                    s.push(e->tujuan);
                }
                e = e->next;
            }
        }
    }
    cout << endl;
}

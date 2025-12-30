#include "graph3.h"
#include <stack>
#include <queue>

void initGraph(Graph &G) {
    G.first = NULL;
}

void insertVertex(Graph &G, DataType x) {
    NodeAdr node = new GraphNode;
    node->value = x;
    node->visited = false;
    node->adj = NULL;
    node->next = NULL;

    if (G.first == NULL) {
        G.first = node;
    } else {
        NodeAdr temp = G.first;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = node;
    }
}

void connectVertex(NodeAdr a, NodeAdr b) {
    if (!a || !b) return;

    EdgeAdr e1 = new EdgeNode;
    e1->link = b;
    e1->next = a->adj;
    a->adj = e1;

    EdgeAdr e2 = new EdgeNode;
    e2->link = a;
    e2->next = b->adj;
    b->adj = e2;
}

void displayGraph(Graph &G) {
    NodeAdr n = G.first;
    while (n != NULL) {
        cout << "Node " << n->value << " terhubung ke: ";
        EdgeAdr e = n->adj;
        while (e != NULL) {
            cout << e->link->value << " ";
            e = e->next;
        }
        cout << endl;
        n = n->next;
    }
}

void resetVisited(Graph &G) {
    NodeAdr temp = G.first;
    while (temp != NULL) {
        temp->visited = false;
        temp = temp->next;
    }
}

void traversalDFS(Graph &G, NodeAdr start) {
    if (start == NULL) return;
    resetVisited(G);

    stack<NodeAdr> s;
    s.push(start);

    cout << "DFS Traversal: ";
    while (!s.empty()) {
        NodeAdr curr = s.top();
        s.pop();

        if (!curr->visited) {
            curr->visited = true;
            cout << curr->value << " - ";

            EdgeAdr e = curr->adj;
            while (e != NULL) {
                if (!e->link->visited) {
                    s.push(e->link);
                }
                e = e->next;
            }
        }
    }
    cout << endl;
}

void traversalBFS(Graph &G, NodeAdr start) {
    if (start == NULL) return;
    resetVisited(G);

    queue<NodeAdr> q;
    q.push(start);
    start->visited = true;

    cout << "BFS Traversal: ";
    while (!q.empty()) {
        NodeAdr curr = q.front();
        q.pop();
        cout << curr->value << " - ";

        EdgeAdr e = curr->adj;
        while (e != NULL) {
            if (!e->link->visited) {
                e->link->visited = true;
                q.push(e->link);
            }
            e = e->next;
        }
    }
    cout << endl;
}

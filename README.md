# <h1 align="center">Laporan Praktikum Modul (14)</h1>
<p align="center">Mario Sebastian Barus</p>

## Dasar Teori
Graph adalah struktur data yang digunakan untuk menggambarkan hubungan antar objek melalui simpul (node) dan sisi (edge), yang bisa bersifat terarah maupun tidak terarah Graph biasanya direpresentasikan dengan adjacency list atau adjacency matrix, sehingga memudahkan operasi seperti menambah, menghapus, dan **menghubungkan simpul. Penelusuran graph bisa dilakukan dengan DFS (menjelajahi sedalam mungkin) atau BFS (menjelajahi per tingkat), yang sangat berguna untuk pemetaan jalur dan analisis jaringan.
## Guided 

### main.cpp
```C++

### graph.h
```C++

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

using namespace std;

typedef char infoGraph;
typedef struct ElmNode *adrNode;
typedef struct ElmEdge *adrEdge;

struct ElmNode {
    infoGraph info;      //menyimpan data node (misal: char/int)
    int visited;        //Penanda untuk traversal (0/1) (penanda apakah node sudah dikunjungi)
    adrEdge firstEdge; //Pointer ke edge pertama yang terhubung
    adrNode Next;     //Pointer ke node berikutnya dalam graph
};

struct ElmEdge {
    adrNode Node;  //Pointer yang menunjuk ke lokasi node tujuan
    adrEdge Next;  //Pointer ke edge berikutnya (jika satu node memiliki banyak cabang)
};

struct Graph {
    adrNode First;  //Pointer ke node pertama dalam list graph
};

void CreateGraph(Graph &G);  //prosedur untuk mengeset fitur dari graph sebagai NULL
adrNode AlokasiNode(infoGraph data);  //alokasi node baru
adrEdge AlokasiEdge(adrNode nodeTujuan);  //alokasi Edge baru

void InsertNode(Graph &G, infoGraph data);  //menambahkan node ke dalam graph
adrNode FindNode(Graph G, infoGraph data);  //function untuk mencari alamat node berdasarkan nilai info yang diberikan
void ConnectNode(Graph &G, infoGraph info1, infoGraph info2); //prosedur untuk menghubungkan dua node (membuat edge dari info1 ke info2)
void DisconnectNode(adrNode node1, adrNode node2);  //prosedur untuk memutuskan hubungan dua node (menghapus edge dari node1 ke node2)
void DeleteNode(Graph &G, infoGraph X);  //prosedur untuk menghapus node X beserta semua Edge yang terhubung

void PrintInfoGraph(Graph G);  //Menampilkan isi graph(Adjency list)
void ResetVisited(Graph &G);  //Reset status visited sebelum traversal
void PrintBFS(Graph G, infoGraph StartInfo);  //traversal Breadth Search / BFS (Menggunakan queue untuk menelusuri node berdasarkan tingkat)
void PrintDFS(Graph G, infoGraph StartInfo);  //traversal Depth First Search / DFS (menggunakan stack untuk menelusuri node secara mendalam)

#endif

```
### graph.cpp
```C++
#include "graph.h"
#include <iostream>
#include <queue> //library queue untuk BFS
#include <stack> //library stack untuk DFS

using namespace std;

//prosedur untuk mengeset first dari graph sebagai NULL
void CreateGraph(Graph &G) {
    G.First = NULL;
}

//alokasi Node baru
adrNode AlokasiNode(infoGraph data) {
    adrNode nodeBaru = new ElmNode;
    nodeBaru->info = data;
    nodeBaru->visited = 0; //isinya 0/1
    nodeBaru->firstEdge = NULL;
    nodeBaru->Next = NULL;
    return nodeBaru;
}

//alokasi Edge baru
adrEdge AlokasiEdge(adrNode nodeTujuan) {
    adrEdge edgeBaru = new ElmEdge;
    edgeBaru->Node = nodeTujuan;
    edgeBaru->Next = NULL;
    return edgeBaru;
}

//Menambahkan Node ke dalam Graph
void InsertNode(Graph &G, infoGraph data) {
    adrNode nodeBaru = AlokasiNode(data);
    if (G.First == NULL) {
        G.First = nodeBaru;
    } else {
        //konsepnya insert last
        adrNode nodeBantu = G.First;
        while (nodeBantu->Next != NULL) {
            nodeBantu = nodeBantu->Next;
        }
        nodeBantu->Next = nodeBaru;
    }
}

//function untuk mencari alamat Node berdasarkan infonya
adrNode FindNode(Graph G, infoGraph data) {
    adrNode nodeBantu = G.First;
    while (nodeBantu != NULL) {
        if (nodeBantu->info == data) {
            return nodeBantu;
        }
        nodeBantu = nodeBantu->Next;
    }
    return NULL;
}

//prosedur untuk menghubungkan dua Node (Undirected Graph)
void ConnectNode(Graph &G, infoGraph info1, infoGraph info2) {
    adrNode node1 = FindNode(G, info1);
    adrNode node2 = FindNode(G, info2);

    if (node1 != NULL && node2 != NULL) {
        //Hubungkan node1 ke node2
        adrEdge Edge1 = AlokasiEdge(node2);
        Edge1->Next = node1->firstEdge; // Insert First pada list edge
        node1->firstEdge = Edge1;

        //Hubungkan node2 ke node1 (Karena Undirected/Bolak-balik)
        adrEdge Edge2 = AlokasiEdge(node1);
        Edge2->Next = node2->firstEdge;
        node2->firstEdge = Edge2;
    } else {
        cout << "Node tidak ditemukan!" << endl;
    }
}

//prosedur untuk memutuskan hubungan dua node
void DisconnectNode(adrNode node1, adrNode node2) {
    if (node1 != NULL && node2 != NULL) {
        adrEdge edgeBantu = node1->firstEdge;
        adrEdge PrevE = NULL;

        //Cari edge yang mengarah ke node2 di dalam list milik node1
        while (edgeBantu != NULL && edgeBantu->Node != node2) {
            PrevE = edgeBantu;
            edgeBantu = edgeBantu->Next;
        }

        if (edgeBantu != NULL) { //jika Edge ditemukan
            if (PrevE == NULL) {
                //Hapus edge pertama
                node1->firstEdge = edgeBantu->Next;
            } else {
                //Hapus edge di tengah/akhir
                PrevE->Next = edgeBantu->Next;
            }
            delete edgeBantu;
        }
    }
}

//prosedur untuk menghapus Node X beserta semua edge yang berhubungan dengannya
void DeleteNode(Graph &G, infoGraph X) {
    //1. Cari Node yang akan dihapus (nodeHapus)
    adrNode nodeHapus = FindNode(G, X);
    if (nodeHapus == NULL) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }

    //2. Hapus semua Edge yang MENGARAH ke nodeHapus (Incoming Edges)
    //cek setiap node di graph, apakah punya edge ke nodeHapus
    adrNode nodeLainnya = G.First;
    while (nodeLainnya != NULL) {
        DisconnectNode(nodeLainnya, nodeHapus); //putus hubungan nodeLainnya ke nodeHapus
        nodeLainnya = nodeLainnya->Next;
    }

    //3. Hapus semua Edge yang KELUAR dari nodeHapus (Outgoing Edges)
    //Deallokasi list edge milik nodeHapus
    adrEdge edgeBantu = nodeHapus->firstEdge;
    while (edgeBantu != NULL) {
        adrEdge tempE = edgeBantu;
        edgeBantu = edgeBantu->Next;
        delete tempE;
    }
    nodeHapus->firstEdge = NULL;

    //4. Hapus nodeHapus dari List Utama Graph
    if (G.First == nodeHapus) {
        //jika nodeHapus di awal
        G.First = nodeHapus->Next;
    } else {
        //jika nodeHapus di tengah/akhir
        adrNode nodeBantu = G.First;
        while (nodeBantu->Next != nodeHapus) {
            nodeBantu = nodeBantu->Next;
        }
        nodeBantu->Next = nodeHapus->Next;
    }

    //5. delete nodeHapus
    delete nodeHapus;
}

//Menampilkan isi Graph (Adjacency List) 
void PrintInfoGraph(Graph G) {
    adrNode nodeBantu = G.First;
    while (nodeBantu != NULL) {
        cout << "Node " << nodeBantu->info << " terhubung ke: ";
        adrEdge edgeBantu = nodeBantu->firstEdge;
        while (edgeBantu != NULL) {
            cout << edgeBantu->Node->info << " "; //Akses info dari node tujuan
            edgeBantu = edgeBantu->Next;
        }
        cout << endl;
        nodeBantu = nodeBantu->Next;
    }
}

//Reset status visited sebelum traversal
void ResetVisited(Graph &G) {
    adrNode nodeReset = G.First;
    while (nodeReset != NULL) {
        nodeReset->visited = 0;
        nodeReset = nodeReset->Next;
    }
}

//traversal Breadth First Search / BFS (Menggunakan Queue)
void PrintBFS(Graph G, infoGraph StartInfo) {
    ResetVisited(G);
    adrNode StartNode = FindNode(G, StartInfo);
    
    if (StartNode == NULL) return;

    queue<adrNode> Qyu;
    
    //Enqueue start
    Qyu.push(StartNode);
    StartNode->visited = 1;

    cout << "BFS Traversal: ";
    while (!Qyu.empty()) {
        adrNode nodeBantu = Qyu.front();
        Qyu.pop();
        cout << nodeBantu->info << " - ";

        //Cek semua tetangga atau edge nya
        adrEdge edgeBantu = nodeBantu->firstEdge;
        while (edgeBantu != NULL) {
            if (edgeBantu->Node->visited == 0) {
                edgeBantu->Node->visited = 1;
                Qyu.push(edgeBantu->Node);
            }
            edgeBantu = edgeBantu->Next;
        }
    }
    cout << endl;
}

//Traversal Depth First Search / DFS (Menggunakan Stack)
void PrintDFS(Graph G, infoGraph StartInfo) {
    ResetVisited(G);
    adrNode StartNode = FindNode(G, StartInfo);
    
    if (StartNode == NULL) return;

    stack<adrNode> Stak;
    
    Stak.push(StartNode);

    cout << "DFS Traversal: ";
    while (!Stak.empty()) {
        adrNode nodeBantu = Stak.top();
        Stak.pop();

        if (nodeBantu->visited == 0) {
            nodeBantu->visited = 1;
            cout << nodeBantu->info << " - ";

            //masukkan tetangga ke stack
            adrEdge edgeBantu = nodeBantu->firstEdge;
            while (edgeBantu != NULL) {
                if (edgeBantu->Node->visited == 0) {
                    Stak.push(edgeBantu->Node);
                }
                edgeBantu = edgeBantu->Next;
            }
        }
    }
    cout << endl;
}


```
main.cpp
```C++
#include "graph.h"
#include "graph.cpp"
#include <iostream>
#include <queue>
#include <stack>
using namespace std;
int main(){
    Graph G;
    CreateGraph(G);

    InsertNode(G, 'A');
    InsertNode(G, 'B');
    InsertNode(G, 'C');
    InsertNode(G, 'D');
    InsertNode(G, 'E');
    InsertNode(G, 'F');
    
    //hubungkan antar node
    ConnectNode(G, 'A', 'B');
    ConnectNode(G, 'A', 'D');
    ConnectNode(G, 'B', 'C');
    ConnectNode(G, 'D', 'C');
    ConnectNode(G, 'B', 'E');
    ConnectNode(G, 'C', 'E');
    ConnectNode(G, 'C', 'F');
    ConnectNode(G, 'E', 'F');

    cout << "=== REPRESENTASI ADJACENCY LIST ===" << endl;
    PrintInfoGraph(G);
    cout << endl;

    cout << "=== HASIL TRAVERSAL ===" << endl;
    //mulai traversal dari node A
    PrintBFS(G, 'A');  //BFS
    PrintDFS(G, 'A');  //DFS
    cout << endl;

    cout << "=== HAPUS NODE E ===" << endl;
    DeleteNode(G, 'E');
    if(FindNode(G, 'E') == NULL) {
        cout << "node E berhasil dihapus" << endl;
    } else {
        cout << "Node E tidak berhasil dihapus" << endl;
    }
    cout << endl;

    cout << "=== REPRESENTASI ADJACENCY LIST ===" << endl;
    PrintInfoGraph(G);
    cout << endl;

    cout << "=== HASIL TRAVERSAL ===" << endl;
    //mulai traversal dari node A
    PrintBFS(G, 'A');  //BFS
    PrintDFS(G, 'A');  //DFS

    return 0;
}

```

## Unguided 

### 1. [main1.cpp]

```C++
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


```
Kode ini merupakan program utama yang digunakan untuk membuat sebuah graph, menghubungkan setiap simpul satu sama lain, lalu menampilkan hasil hubungan graph yang telah dibentuk.
#### Full code Screenshot:
<img width="460" height="544" alt="image" src="https://github.com/user-attachments/assets/34aa7127-48de-462c-ae96-e05782efdd98" />

### [graph1.cpp]

```C++
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

```

Kode ini merupakan file yang mengatur proses pembuatan dan pengelolaan graph, seperti menambahkan simpul, menghubungkan simpul satu dengan yang lain, serta menampilkan hubungan antar simpul secara sederhana.
#### Full code Screenshot:
<img width="428" height="581" alt="image" src="https://github.com/user-attachments/assets/bec6fbc4-8c68-47dc-8369-264840798bc7" />
<img width="541" height="231" alt="image" src="https://github.com/user-attachments/assets/0d5e5fba-c250-443d-82ae-09d5018e9fce" />



### [graph1.h]

```C++
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

```

#### Output:
<img width="385" height="177" alt="image" src="https://github.com/user-attachments/assets/19807294-780f-4924-af3b-3bcf3f8d8fc2" />

File header ini berfungsi sebagai dasar pembentukan struktur graph. Di dalamnya terdapat definisi node, edge, dan graph, serta deklarasi fungsi untuk menambah simpul, menghubungkan simpul, dan menampilkan graph.
#### Full code Screenshot:
<img width="339" height="493" alt="image" src="https://github.com/user-attachments/assets/ae393057-623c-4e08-a437-74416e8f0f18" />

### 2. [main2.cpp]

```C++
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

```
Kode ini merupakan program utama yang membangun sebuah graph, menghubungkan setiap simpul sesuai relasi yang ditentukan, menampilkan daftar hubungan antar simpul, dan melakukan traversal DFS untuk mengeksplorasi seluruh simpul dari titik awal.
#### Full code Screenshot:
<img width="597" height="572" alt="image" src="https://github.com/user-attachments/assets/a9e6596a-9108-4a53-ba03-fce2da341794" />

### [graph2.cpp]

```C++
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


```

Program ini membuat graph dengan menambahkan simpul dan menghubungkannya, menampilkan hubungan antar simpul, serta menjelajahi seluruh simpul menggunakan DFS dari titik awal yang ditentukan.
#### Full code Screenshot:
<img width="528" height="608" alt="image" src="https://github.com/user-attachments/assets/6f62f7d2-5167-4973-996e-65a033bd5c51" />
<img width="443" height="600" alt="image" src="https://github.com/user-attachments/assets/e07bb836-0f2d-4c74-a235-2fcab25a008e" />


### [graph2.h]

```C++
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

```

#### Output:
<img width="525" height="207" alt="image" src="https://github.com/user-attachments/assets/8e7b93fe-8f3a-42af-8baa-43884b3d3ec5" />

Header ini menetapkan struktur graph berbasis linked list, dengan simpul (`Node`) dan sisi (`Edge`). Selain itu, disediakan fungsi-fungsi untuk membuat graph, menambah dan menghubungkan simpul, menampilkan relasi antar simpul, serta menjelajahi graph menggunakan DFS.

#### Full code Screenshot:
<img width="476" height="539" alt="image" src="https://github.com/user-attachments/assets/96c2c85f-632f-46ef-b688-ef16d707c884" />

### 3. [main3.cpp]

```C++
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


```
Program utama ini membuat sebuah graph dengan menambahkan beberapa simpul, menghubungkan simpul-simpul sesuai relasi yang ditentukan, menampilkan daftar hubungan antar simpul, dan menelusuri graph dari simpul awal menggunakan **DFS** dan **BFS**.

#### Full code Screenshot:
<img width="438" height="533" alt="image" src="https://github.com/user-attachments/assets/4d12a823-07c2-44d6-985d-be79708e87e1" />

### [graph3.cpp]

```C++
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


```

Kode ini membangun graph menggunakan linked list, menambahkan simpul dan menghubungkannya secara dua arah. Program dapat menampilkan daftar hubungan antar simpul serta menelusuri seluruh graph dari simpul awal menggunakan **DFS** (depth-first search) dan **BFS** (breadth-first search). Fungsi `resetVisited` memastikan setiap traversal dimulai dengan simpul belum dikunjungi.
#### Full code Screenshot:
<img width="335" height="594" alt="image" src="https://github.com/user-attachments/assets/37f20cb5-9ad5-4800-9493-34780465995b" />
<img width="291" height="569" alt="image" src="https://github.com/user-attachments/assets/8f505b1b-98b0-47fa-9c8d-9d426cad4967" />


### [graph3.h]

```C++
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

```

#### Output:
<img width="457" height="257" alt="image" src="https://github.com/user-attachments/assets/fe7e3510-f415-40c6-8aa8-75511b361043" />

Header ini menjelaskan struktur graph menggunakan linked list, dengan simpul (`GraphNode`) yang terhubung melalui sisi (`EdgeNode`). Di dalamnya juga didefinisikan fungsi-fungsi untuk membuat graph, menambahkan dan menghubungkan simpul, menampilkan relasi antar simpul, serta menjelajahi graph dengan metode **DFS** dan **BFS**.

#### Full code Screenshot:
<img width="501" height="553" alt="image" src="https://github.com/user-attachments/assets/f4029f4c-fa72-4f35-ac00-39740e1f8e3f" />


## Kesimpulan
Graph adalah struktur data yang luwes dan efisien untuk menggambarkan keterkaitan antar objek. Dengan memanfaatkan **simpul** dan **sisi**, serta didukung cara penelusuran seperti **DFS** dan **BFS**, graph mempermudah proses analisis jaringan, pencarian jalur, serta pengelolaan data secara teratur dan sistematis.
## Referensi
[1] Skiena, S. S. (2008). The Algorithm Design Manual (2nd ed.). Springer.
[2] Sedgewick, R., & Wayne, K. (2011). Algorithms (4th ed.). Addison-Wesley.
[3] Goodrich, M. T., Tamassia, R., & Goldwasser, M. H. (2014). Data Structures and Algorithms in C++ (2nd ed.). Wiley.
[4] Cormen, T. H., Leiserson, C. E., Rivest, R. L., & Stein, C. (2009). Introduction to Algorithms (3rd ed.). MIT Press.

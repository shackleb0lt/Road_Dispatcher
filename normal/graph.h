#ifndef MYGRAPH_H
#define MYGRAPH_H
#include <iostream>
#include <vector>
#include <queue>

#ifndef NULL
#define NULL nullptr
#endif

using namespace std;
class Node
{
    public:
    int id;                     // Stores the id number of the node
    Node * prev;                // Pointer to previous node on the road
    unsigned int total_time;    // Total time taken to reach this node from source
    unsigned int total_pot;     // Total pots encountered to reach this node from source
    Node(int u=-1);             // Constructor
};

class Edge
{
    public:
    int to_id;                              // Adjacent Node ID
    unsigned int to_time;                   // Time to travel two adjacent nodes
    unsigned int to_pot;                    // Number of pots between two adjacent node
    Edge(int to=-1,int time=-1,int pot=-1); //COnstructor

};

class Graph
{
    public:
    Node* Vertices[5001];                       // Array stroing all nodes
    vector<Edge*> Adj[5001];                    // Adjacency list of all edges

    int src;                                    // Source node id
    int dest;                                   // Destination node id
    int max_pot;                                // Allowed limit for pots encountered

    Graph(int s,int d,int m);                   // Constructor
    void addEdge(int u,int v, int t,int p);     // Updating edges
    int shortest();                             // Djkistra's Algorithm
};

#endif
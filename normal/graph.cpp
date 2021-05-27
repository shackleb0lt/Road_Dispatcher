#include "graph.h"


/**
 * Constructor for Node class
 * @param u node id
*/
Node::Node(int u)
{
    id = u;
    prev = NULL;
    total_time = -1;
    total_pot = -1;
}

/**
 * Constructor for Edge class
 * @param s source node id
 * @param d destination node id
 * @param m maximum pots that can be encountered on the road
*/
Edge::Edge(int to,int time,int pot)
{
    to_id = to;
    to_time = time;
    to_pot = pot;
}

/**
 * Constructor for Graph class
 * @param s source node id
 * @param d destination node id
 * @param m maximum pots that can be encountered on the road
*/
Graph::Graph(int s,int d,int m)
{
    src = s;
    dest = d;
    max_pot = m;

    for(int i=0;i<5001;i++)Vertices[i] = NULL;
}

/**
 * Function that updates edges in the graph
 * @param u source node id
 * @param v destination node id
 * @param p pots on the road between node u and node v
*/
void Graph::addEdge(int u,int v, int t,int p)
{
    if(Vertices[u]==NULL)Vertices[u] = new Node(u);

    if(Vertices[v]==NULL)Vertices[v] = new Node(v);

    Edge *temp_u = new Edge(v,t,p); // edge from u to v
    Edge *temp_v = new Edge(u,t,p); // edge from v to u

    Adj[u].push_back(temp_u);
    Adj[v].push_back(temp_u);
}

//Comparator for the priority queue for djkistra's
struct compare
{
    bool operator()(const Node * a, const Node * b)
    {
        if(a->total_time == b->total_time) return a->total_pot > b->total_pot;
        return a->total_time > b->total_time;
    }
};

/**
 * Function that runs Djkistra's algorithm on all nodes
 * @return Time taken to go from source to destination
*/
int Graph::shortest()
{
    // Priority queue to store the relaxed nodes with top node having least distance from source
    priority_queue<Node*, vector<Node*>, compare> pq; 

    //Initializing source atrributes
    Vertices[src]->total_pot=0;
    Vertices[src]->total_time=0;

    // Adding source to the priority queue
    pq.push(Vertices[src]);
    int u,v;

    while(!pq.empty())
    {
        Node * temp = pq.top(); // Extracting Node with least distance from source
        pq.pop(); 
        u = temp->id;

        for(int i=0;i<Adj[u].size();i++)    // Visiting each of it's neighbouring nodes
        {
            v = Adj[u][i]->to_id;

            // If edge cannot be relaxed move to next node
            if(Vertices[v]->total_time <= Vertices[u]->total_time + Adj[u][i]->to_time) continue;
            
            // If pots encountered exceed the allowed limit move to next node
            if( max_pot < Vertices[u]->total_pot + Adj[u][i]->to_pot) continue;

            //Relax the edge/node with updated values
            Vertices[v]->prev = Vertices[u];
            Vertices[v]->total_time = Vertices[u]->total_time + Adj[u][i]->to_time;
            Vertices[v]->total_pot = Vertices[u]->total_pot + Adj[u][i]->to_pot;

            //Push the realxed node into priority queue
            pq.push(Vertices[v]);
        }
    }

    if(Vertices[dest]==NULL) return -1;         // Checking if any roads lead to destination node
    if(Vertices[dest]->prev==NULL) return -1;   // Checking if any feasible path leads to destination from source
    return Vertices[dest]->total_time;          // Returning the most feasible time
}
#include "city.h"
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;


City::City() 
{
    roadMap = Graph(5001);                                  //Initializing graph of vertex size 5001
    v_pot = get(boost::vertex_distance, roadMap);           //property_map for pot encountered to reach this vertex
    v_time = get(boost::vertex_discover_time, roadMap);     //property_map for time required to reach this vertex
    e_pot = get(boost::edge_weight,roadMap);                //property_map for whether road has pot or not 
    e_time = get(boost::edge_weight2,roadMap);              //property_map for time taken to travel this  road
}


void City::addRoad(Intersection intersection1, Intersection intersection2, unsigned time, bool pothole) 
{
    unsigned nV = num_vertices(roadMap);
    while (intersection1 >= nV)
        nV = add_vertex(roadMap)+1;

    while (intersection2 >= nV)
        nV = add_vertex(roadMap)+1;

    
    auto e = add_edge(intersection1, intersection2, roadMap).first;
    
	/*** Store the time & pothole information for this road. */
    v_pot[intersection1]=0;
    v_pot[intersection2]=0;
    v_time[intersection1]=-1;
    v_time[intersection2]=-1;
    e_time[e] = time;
    e_pot[e] = pothole;
}



int City::findFastestRoute(Intersection from, Intersection to, unsigned potholeLimit) const
{
    //Initializing source and destination values
    v_pot[from] = 0;
    v_time[from] = 0;

    v_pot[to] = 0;
    v_time[to] = -1; 

    //Queue to store the relaxed vertices
    queue<Intersection, list<Intersection> > q;
    q.push(from); //pushing the source into queue

    // // From each vertex in queue, update distances of adjacent vertices
    while (!q.empty())
    {
        Intersection v = q.front();
        q.pop();
        auto outGoing = out_edges(v, roadMap); // extracting the edges from v to it's adjacent vertices
        for (auto e = outGoing.first; e != outGoing.second; ++e)
        {
            Intersection w = target(*e, roadMap);

            if(v_time[w] < v_time[v] + e_time[*e])continue; //Check if the edge can be relaxed

            if(potholeLimit < v_pot[v] + e_pot[*e])continue; //Check if the pothole limit is crossed
            
            v_time[w] = v_time[v] + e_time[*e]; //If the edge can be relaxed update the time take to reach this vertex
            v_pot[w] = v_pot[v] + e_pot[*e];    //Update the number of pots encountered to reach this vertex

            q.push(w);  //push the relaxed vertex into queue

        }
    }
    return v_time[to];

}



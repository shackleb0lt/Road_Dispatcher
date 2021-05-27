#ifndef CITY_H
#define CITY_H

#include <vector>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

class City
{
    typedef boost::property<boost::vertex_distance_t, unsigned int , boost::property<boost::vertex_discover_time_t,unsigned int> > VertexProperty;
    typedef boost::property<boost::edge_weight_t, bool, boost::property<boost::edge_weight2_t,unsigned int> >EdgeProperty;
    
    typedef boost::adjacency_list<boost::listS,       // store edges in lists
                                  boost::vecS,        // store vertices in a vector
                                  boost::undirectedS,
                                  VertexProperty,
                                  EdgeProperty> Graph;

    typedef boost::graph_traits<Graph> GraphTraits;
    typedef GraphTraits::vertex_descriptor Vertex;
    typedef GraphTraits::edge_descriptor Edge;

    Graph roadMap;
  
    /*** You may add additional private data & functions as desired. */

public:
    typedef Vertex Intersection;
    boost::property_map<Graph, boost::vertex_distance_t>::type v_pot;
    boost::property_map<Graph, boost::vertex_discover_time_t>::type v_time;
    boost::property_map<Graph,boost::edge_weight_t>:: type e_pot;
    boost::property_map<Graph,boost::edge_weight2_t>:: type e_time;
    

    /**
     * Construct a new City object with no roads and intersections.
     * 
     */
    City();

    /**
     * Add a new road connecting two intersections.
     * 
     * @param intersection1  Identifier of 1st intersection
     * @param intersection2  Identifier of 2nd intersection
     * @param time How many minutes required to travel this road between the two intersections
     * @param pothole  true iff this road contains a pothole
     */
    void addRoad(Intersection intersection1, Intersection intersection2, unsigned time, bool pothole);

    /**
     * Find the total time of the shortest path between two intersections that will
     * not break an axle.
     * 
     * @param from The starting interestion of the vehicle
     * @param to  The ending intersection of the vehicle
     * @param potholeLimit the maximum number of potholes the vehicle may traverse
     * @return int The total time required to go from "from" to "to" while traversing no more
     *             than potholeLimit potholes.  Return -1 if there is no acceptable path between
     *             the two intersections.
     */
    int findFastestRoute(Intersection from, Intersection to, unsigned potholeLimit) const;

};

#endif

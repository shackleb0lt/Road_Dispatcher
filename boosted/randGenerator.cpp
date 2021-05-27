#include <iostream>

#include <ctime>
#include <cstdlib>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

using namespace std;
using namespace boost;




typedef boost::adjacency_list<boost::setS, // store edges in lists
		                      boost::vecS, // store vertices in a vector
							  boost::undirectedS // an undirected graph,
							  // no bundled properties on vertices & edges
							  >
                                Graph;
typedef boost::graph_traits<Graph> GraphTraits;
typedef GraphTraits::vertex_descriptor Vertex;
typedef GraphTraits::edge_descriptor Edge;



void generate(int nV, int nE, int pathLen)
{
	Graph g(nV);

	if (pathLen > nE)
		pathLen = nE;

	cout << "0 " << nV-1 << " 4" << endl;

	// Generate a path of length pathLen from vertex 0 to
	// vertex nV-1.  There may be other paths, both shorter and longer,
	// in the completed graph, but this one at least is guaranteed to
	// exist.
	Vertex v = 0;
	for (int i = 0; i < pathLen-1; ++i)
	{
		bool OK = false;
		Vertex w = v;
		do
		{
			w = rand() % (nV-1);
			if (v == w) continue;
			//if (edge(v,w,g).second) continue;
			auto check = add_edge(v, w, g);
			// cerr << "tried " << v << "," << w << ": " << check.second << endl;
			OK = check.second;
		} while (!OK);
		v = w;
	}
	add_edge(v, nV-1, g);
	//cerr << "Added " << v << "," << nV-1 << endl;

	// Add additional edges to the graph
	for (int i = pathLen; i < nE; ++i)
	{
		bool OK = false;
		int attempts = 0;
		do
		{
			Vertex v = rand() % nV;
			Vertex w = rand() % nV;
			if (v == w) continue;
			//if (edge(v,w,g).second) continue;
			auto check = add_edge(v, w, g);
			// cerr << "tried " << v << "," << w << ": " << check.second << endl;
			OK = check.second;
			++attempts;
			if (attempts > 1000) break;
		} while (!OK);
	}


	// List the graph
	auto alledges = edges(g);
	for (auto ei = alledges.first; ei != alledges.second; ++ei)
	{
		Vertex v = source(*ei, g);
		Vertex w = target(*ei, g);
		cout << v << ' ' << w << ' ' << 1+(rand() % 20) << ' ' << ((rand() % 4) == 0)  << endl;
	}
}


/**
 * Random graph generator: ./randGenerator nV nE pathLen
 */
int main (int argc, char** argv)
{
	if (argc != 4)
	{
		// cerr << "Usage: " << argv[0] << "nVertices nEdges desiredPathLen" << endl;
		return -1;
	}

	srand(time(0));

	int nV =  std::stoi(argv[1]);
	int nE =  std::stoi(argv[2]);
	int pathLen =  std::stoi(argv[3]);

	generate(nV, nE, pathLen);
	return 0;

}

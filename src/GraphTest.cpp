#include "../inc/Graph.h"
#include "../inc/Edge.h"
#include "../inc/Node.h"

int main()
{
	double params0to1[] = {1,1,1,1};
	double params1to2[] = {2,1,1,1};
	double params0to2[] = {3,2,3,4};
	Graph graph;
	
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();
	graph.addEdgeMST(Edge(1, params0to1), 0, 1);
	graph.addEdgeMST(Edge(1, params1to2), 1, 2);
	graph.addEdgeMST(Edge(1, params0to2), 0, 2);
	
	std::cout<<graph<<"\n\n\n\nComputing MST...\n\n\n\n\n";
	Graph mst = graph.MST();
	std::cout<<mst;
	return 0;
}


#include "../inc/Graphics.h"
#include "../inc/Graph.h"
#include "../inc/Edge.h"
#include "../inc/Node.h"


Graph getMST();

int main ()
{
	Window win;
	GC gc;
	//Init display
	Display *dis = create_window(win, gc);
	
	//Run mst/get from file?
	double params0to1[] = {1,1,1,1};
	double params1to2[] = {2,1,1,1};
	double params0to2[] = {3,2,3,4};
	double params2to3[] = {2,2,3,4};
	Graph graph;
	
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();
	graph.addEdgeDouble(Edge(1, params0to1), 0, 1);
	graph.addEdgeDouble(Edge(1, params1to2), 1, 2);
	graph.addEdgeDouble(Edge(1, params0to2), 0, 2);
	graph.addEdgeDouble(Edge(1, params2to3), 2, 3);
	
	Graph mst = graph.MST();
	draw_graph(dis, win, gc, mst);
	hold_window(dis, win);
	draw_graph(dis, win, gc, graph);
	hold_window(dis, win);
	close_window(dis, win, gc);
}

Graph getMST()
{
	double params0to1[] = {1,1,1,1};
	double params1to2[] = {2,1,1,1};
	double params0to2[] = {3,2,3,4};
	double params2to3[] = {2,2,3,4};
	Graph graph;
	
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();
	graph.addVertex();
	graph.addEdgeDouble(Edge(1, params0to1), 0, 1);
	graph.addEdgeDouble(Edge(1, params1to2), 1, 2);
	graph.addEdgeDouble(Edge(1, params0to2), 0, 2);
	graph.addEdgeDouble(Edge(1, params2to3), 2, 3);
	
	Graph mst = graph.MST();
	return mst;
}

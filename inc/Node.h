#ifndef NODE_H
#define NODE_H

#include "Edge.h"
#include <vector>

struct Node
{
	public:	
		int node_id; //Used for graph traversal
		int priority;
		std::vector<Edge> node_edges; //Dynamic list of edges
		
		//Default constructor - SHOULD NOT BE USED FOR INSTANSIATED NODES
		Node() : node_id(-1), node_edges() { }
		
		//Overloaded constructors for specifying an id with an option for preset edges as well (CopyC?)
		Node(const int name) : node_id(name), priority(), node_edges() { }
		Node(const int name, const std::vector<Edge> edges) : node_id(name), priority(), node_edges() 
		{
			for(Edge e : edges)
			{
				addEdge(e); //Add the edges like this so that they are properly anchored to this node
			}
		}
		Node(const int name, const int pri) : node_id(name), priority(pri), node_edges(){}
		
		//Adds the edge to the node list and anchor it to this node
		void addEdge(Edge edge_in)
		{
			edge_in.beginning = this;
			//Only add unique edges
			for(Edge e : node_edges)
			{
				if(e.isSame(edge_in))
				{
					return;
				}
			}
			node_edges.push_back(edge_in);
		}
		
		//Overloaded operators
		friend std::ostream& operator<<(std::ostream& output, Node& node_in)
		{
			output<<"Node: "<<node_in.node_id<<"\n\tConnections: "<<std::endl;
			output<<"\tNumber of edges: "<<node_in.node_edges.size();
			for(Edge e : node_in.node_edges)
			{
				int edgeEnd = (e.destination)->node_id;
				output<<std::endl<<"\t\t(Endpoint: "<<edgeEnd<<", Weight: "<<e.getWeight()<<") ";
			}
			output<<std::endl;
			return output;
		}
		//Nodes are only the same if they are the same object
		bool operator!=(const Node rhs) const
		{
			return this != (void *)&rhs;
		}
		bool operator==(const Node rhs) const
		{
			return this == (void *)&rhs;
		}
	
};



#endif

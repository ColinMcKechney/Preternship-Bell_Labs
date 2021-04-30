#ifndef NODE_H
#define NODE_H

#include "Edge.h"
#include <algorithm>
#include <vector>

struct Node
{
	public:		
		
		int node_id;
		std::vector<Edge> node_edges;
		
		Node() : node_id(), node_edges() { }
		
		Node(const int name) : node_id(name), node_edges() { }
		Node(const int name, const std::vector<Edge> edges) : node_id(name), node_edges() 
		{
			for(Edge e : edges)
			{
				addEdge(e);
			}
		}
		
		void addEdge(Edge edge_in)
		{
			edge_in.begining = this;
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
		
		friend std::ostream& operator<<(std::ostream& output, Node& node_in)
		{
			output<<"ID:"<<node_in.node_id<<std::endl;
			for(Edge e : node_in.node_edges)
			{
				output<<"\tEdge - "<<e<<'\n';
			}
			return output;
		}
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
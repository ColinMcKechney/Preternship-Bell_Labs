#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <queue> //Needed for priority Queue

class Graph
{
	public:
	
		std::vector<Node> verticies; //Vector containing all the Nodes
		int vertexCount; //Number of nodes in the graph
		
		//Default constructor, all graphs are constructed from scratch
		Graph() : verticies(), vertexCount(0) {}
		
		//These add verticies in various overloads for ease of use
		void addVertex()
		{
			verticies.push_back(Node(vertexCount));
			vertexCount++;
		}
		void addVertex(const Node node_in)
		{
			verticies.push_back(node_in);
			vertexCount++;
		}
		void addVertex(const std::vector<Edge> edges)
		{
			verticies.push_back(Node(vertexCount, edges));
			vertexCount++;
		}
		void addBlankNode(const Node n)
		{
			verticies.push_back(Node(n.node_id));
			vertexCount++;
		}
		
		//Adds an edge with various overloads for ease of use
		void addEdge(const Edge edge_in)
		{
			getNode((edge_in.beginning)->node_id)->addEdge(edge_in);
		}
		void addEdge(const Edge edge_in, const Node* start)
		{
			verticies[start->node_id].addEdge(edge_in);
		}
		void addEdge(const Edge edge_in, const unsigned int start)
		{
			verticies[start].addEdge(edge_in);
		}
		//addEdgeDouble creates a double sided node instead of a single
		void addEdgeDouble(const Edge edge_in, const int start, const int end)
		{
			Edge newEdge1 = edge_in;
			newEdge1.destination = &verticies[end];
			verticies[start].addEdge(newEdge1);
			Edge newEdge2 = edge_in;
			newEdge2.destination = &verticies[start];
			verticies[end].addEdge(newEdge2);
		}
		//addEdgeMST creates a single sided node for visualization purposes
		void addEdgeMST(const Edge edge_in, const int start, const int end)
		{
			Edge newEdge1 = edge_in;
			newEdge1.destination = &verticies[end];
			verticies[start].addEdge(newEdge1);
		}
		
		//Calculates and returns a new graph with minimized path weight between nodes
		Graph MST(const int startNode) const
		{
			Graph graph_out;
			//First, reinitialize all the existing nodes in the new graph

			for(Node n : verticies)
			{
				graph_out.addBlankNode(n);
			}
			
			
			//Stores the lowest weight for each vertex
			double* lowestWeights = new double[vertexCount];
			
			//Create the visited table and set the root to visitedx
			std::unordered_map<int, bool> visited;
			for(Node n : verticies)
			{
				visited[n.node_id] = false;
				lowestWeights[n.node_id] = 2147483647;
			}
			
			//Map of all the edges that will be used in the final graph
			std::unordered_map<int, Edge> finalEdges;
			
			//Initialize the priority queue with the first node's edges
			std::priority_queue<Edge> prioQueue;
			//Continues until all nodes are checked
			//Begin at the root node
			Node currentNode = verticies[startNode];
			//Set the origin node to visited
			visited[startNode] = true;
			do //First run will always complete unless there is no nodes, in which case there is no graph!
			{
				std::cout<<std::endl<<"Current Node: "<<currentNode<<std::endl; //Verbose testing
				//Checks all edges in this node and identifies that the node has been checked
				int nodeId = currentNode.node_id;
				visited[nodeId] = true;
				//Finds the lowest weight edge for the current node
				Edge edgeLowest;
				for(Edge e : currentNode.node_edges)
				{
					std::cout<<"Checking edge ("<<e.beginning->node_id<<" to "<<e.destination->node_id<<")\n"; //Verbose testing
					if(lowestWeights[nodeId] > e.getWeight())
					{
						lowestWeights[nodeId] = e.getWeight();
						edgeLowest = e;
					}
				}
				//Run through loop again and add non-lowest edges to queue
				for(Edge e : currentNode.node_edges)
				{
					if(edgeLowest.isSame(e)) //If this edge is the lowest, put it in the final edge and don't put it in queue
					{
						std::cout<<"Found edge ("<<e.beginning->node_id<<" to "<<e.destination->node_id<<")\n"; //Verbose testing
						finalEdges[nodeId] = e;
					}
					if(!visited[e.destination->node_id]) //If the ddestination node hasn't already been visited, put it in the queue
					{
						std::cout<<"Pushing edge ("<<e.beginning->node_id<<" to "<<e.destination->node_id<<")\n"; //Verbose testing
						prioQueue.push(e);
					} else //If the node has been visited, no need to put it in queue
					{
						std::cout<<"Already checked ("<<e.beginning->node_id<<" to "<<e.destination->node_id<<")\n"; //Verbose testing
					}
				}
				//Checks for the next node to use
				Edge topEdge;
				int oldNode = currentNode.node_id;
				while(!prioQueue.empty() && visited[currentNode.node_id]) //Continue until there is no more PQ or finds a node that hasn't been visited
				{
					topEdge = prioQueue.top();
					prioQueue.pop();
					currentNode = verticies[topEdge.destination->node_id];
					std::cout<<"\nTrying to check node "<<currentNode.node_id<<std::endl; //Verbose testing
				}
				if(currentNode.node_id == oldNode) //If there is no new nodes in the prioQueue, then we're all done!
				{
					std::cout<<"Couldn't find a free node, all done!\n";
					break;
				}
				std::cout<<"\nIs node "<<currentNode.node_id<<" visited?: "<<visited[currentNode.node_id]<<std::endl; //Verbose testing
			} while(!prioQueue.empty() || !visited[currentNode.node_id]); //Continue until the queue is empty or no new nodes could be found
			//Create the new edges on the MST graph
			for(int i = 0; i < vertexCount; i++)
			{
				if(finalEdges.count(i) != 0)
				{
					graph_out.addEdgeMST(finalEdges.at(i), i, (finalEdges.at(i).destination)->node_id);
				} else
				{
					std::cout<<"Does not contain an edge with node "<<i<<std::endl; //Verbose testing
				}
			}
			return graph_out;
		}
		
		Node* getNode(const int node_id){
			//finds node based on node_id and returns a pointer to it
			for(size_t x =0; x<verticies.size(); x++){
				if(node_id == verticies[x].node_id)
					return &verticies[x];
			}
			return NULL;
		}

		//Output overload
		friend std::ostream& operator<<(std::ostream& output, const Graph& graph_in)
		{
			if(graph_in.vertexCount == 0)
			{
				output<<"Graph is Empty"<<std::endl;
				return output;
			}
			for(Node element : graph_in.verticies)
			{
				output<<element<<std::endl;
			}
			return output;
		}
};

#endif
#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"
#include <queue>

class Graph
{
	public:
		std::vector<Node> verticies;
		int vertexCount;
		
		Graph() : verticies(), vertexCount(0) {}
		
		void addVertex()
		{
			verticies.push_back(Node(vertexCount));
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
		
		void addEdge(Edge edge_in)
		{
			verticies[(edge_in.begining)->node_id].addEdge(edge_in);
		}
		void addEdge(Edge edge_in, Node* start)
		{
			verticies[start->node_id].addEdge(edge_in);
		}
		void addEdge(Edge edge_in, unsigned int start)
		{
			verticies[start].addEdge(edge_in);
		}
		void addEdgeMST(const Edge edge_in, int start, int end)
		{
			Edge newEdge1 = edge_in;
			newEdge1.destination = &verticies[end];
			verticies[start].addEdge(newEdge1);
			Edge newEdge2 = edge_in;
			newEdge2.destination = &verticies[start];
			verticies[end].addEdge(newEdge2);
			std::cout<<"\nAdding edge:\n";
			std::cout<<newEdge1;
			std::cout<<"\n\n";
		}
		
		Graph MST()
		{
			Graph graph_out;
			//First, reinitialize all the nodes in the new graph
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
			visited[0] = true;
			
			std::unordered_map<int, Edge> finalEdges;
			
			//Initialize the priority queue with the first node's edges
			std::priority_queue<Edge> prioQueue;
			//Continues until all nodes are checked
			//Begin at the root node
			Node currentNode = verticies[0];
			do 
			{
				std::cout<<std::endl<<"Current Node: "<<currentNode<<std::endl;
				//Checks all edges in this node
				int nodeId = currentNode.node_id;
				visited[nodeId] = true;
				Edge edgeLowest;
				for(Edge e : currentNode.node_edges)
				{
					std::cout<<"Checking edge ("<<e.begining->node_id<<" to "<<e.destination->node_id<<")\n";
					if(lowestWeights[nodeId] > e.getWeight())
					{
						std::cout<<"Lower than "<<lowestWeights[nodeId];
						lowestWeights[nodeId] = e.getWeight();
						edgeLowest = e;
					}
				}
				//Run through loop again and add non-lowest edges to queue
				for(Edge e : currentNode.node_edges)
				{
					if(edgeLowest.isSame(e))
					{
						std::cout<<"Found edge ("<<e.begining->node_id<<" to "<<e.destination->node_id<<")\n";
						finalEdges[nodeId] = e;
					} else if(!visited[e.destination->node_id])
					{
						std::cout<<"Pushing edge ("<<e.begining->node_id<<" to "<<e.destination->node_id<<")\n";
						prioQueue.push(e);
					} else
					{
						std::cout<<"Already checked ("<<e.begining->node_id<<" to "<<e.destination->node_id<<")\n";
					}
				}
				Edge topEdge = prioQueue.top();
				std::cout<<"Nodes: "<<(!prioQueue.empty() ? "Not Empty" : "Empty")<<"\n\n\n\n";
				int oldNode = currentNode.node_id;
				while(!prioQueue.empty())
				{
					topEdge = prioQueue.top();
					prioQueue.pop();
					//int edgeStart = (topEdge.begining)->node_id;
					//int edgeEnd = (topEdge.destination)->node_id;
					currentNode = verticies[topEdge.destination->node_id];
					std::cout<<"\nTrying to check node "<<currentNode.node_id<<std::endl;
				}
				if(currentNode.node_id == oldNode)
				{
					std::cout<<"Couldn't find a free node!";
					break;
				}
				std::cout<<"\nIs node "<<currentNode.node_id<<" visited?: "<<visited[currentNode.node_id]<<std::endl;
			} while(!prioQueue.empty() || !visited[currentNode.node_id]);
			for(int i = 0; i < vertexCount; i++)
			{
				if(finalEdges.count(i) != 0)
				{
					graph_out.addEdgeMST(finalEdges.at(i), i, (finalEdges.at(i).destination)->node_id);
				} else
				{
					std::cout<<"Does not contain an edge with node "<<i<<std::endl;
				}
			}
			return graph_out;
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
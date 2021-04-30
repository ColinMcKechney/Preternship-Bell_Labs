#ifndef EDGE_H
#define EDGE_H

#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <unordered_map>

//Used to define the different newtwork slice types to identify which optimization method should be used
enum NetworkSliceType
{
	NoSlice = 0,
	Broadband = 1,
	MissionCritical = 2,
};

//Used to identify the different types of parameters, as well as the number of them
const int numParameters = 4;
enum ParameterType
{
	Latency = 0,
	DataThroughput = 1,
	Reliability = 2,
	Mobility = 3,
};

struct Node;
struct Edge
{
	private:
		
		NetworkSliceType sliceType; //Identifies how the weight is calculated
		std::unordered_map<int, double> param; //Array of parameters to optimize the network slice
		double weight; //Stores the weight so it isn't recalculated upon calling each time
		
		//Default funciton for error catching
		double weight_NoSlice() const 
		{
			std::cout<<"No Slice Type Selected";
			return 0;
		}
		//Functions that calculate the weight of the edge, simplified for now
			//needs proper investigation once simulation is completed 
		double weight_Broadband()
		{
			return param[ParameterType::Latency];
		}
		double weight_MissionCritical()
		{
			return param[ParameterType::Latency] + param[ParameterType::Reliability];
		}
		
	public:
		Node* begining;
		Node* destination;
		
		//Default Constructor
		Edge() : sliceType(NetworkSliceType::NoSlice), param(), weight(), begining(NULL), destination(NULL) {}
		
		//Constructors, allowing for multiple overloads but upon implementation, one will be chosed
		Edge(const int type_in, const std::unordered_map<int, double> param_in, Node* start = NULL, Node* end = NULL) : sliceType((NetworkSliceType)type_in), param(param_in), weight(), begining(start), destination(end) {getWeight(sliceType);}
		Edge(const NetworkSliceType type_in, const std::unordered_map<int, double> param_in, Node* start = NULL, Node* end = NULL) : sliceType(type_in), param(param_in), weight(), begining(start), destination(end) {getWeight(sliceType);} //Prefered to use for implementation
		Edge(const int type_in, const double param_in[], Node* start = NULL, Node* end = NULL) : sliceType((NetworkSliceType)type_in), param(), weight(), begining(start), destination(end) {
			for(int i = 0; i < numParameters; i++)
			{
				param[i] = param_in[i];
			}
			getWeight(sliceType);
		}
		Edge(const NetworkSliceType type_in, const double param_in[], Node* start = NULL, Node* end = NULL) : sliceType(type_in), param(), weight(), begining(start), destination(end) {
			for(int i = 0; i < numParameters; i++)
			{
				param[i] = param_in[i];
			}
			getWeight(sliceType);
		}
		
		//Simple accessor of weight variable
		double getWeight() const
		{
			return weight;
		}
		//Gets the weight according to the slice type specified and switch the saved type to this
		double getWeight(const NetworkSliceType type)
		{
			sliceType = type;
			switch(type)
			{
				case NetworkSliceType::Broadband:
					weight = weight_Broadband();
					break;
				case NetworkSliceType::MissionCritical:
					weight = weight_MissionCritical();
					break;
				case NetworkSliceType::NoSlice:
				default:
					weight = weight_NoSlice();
					break;
			}
			return weight;
		}
		
		//Output overload
		friend std::ostream& operator<<(std::ostream& output, Edge& edge_in)
		{
			for(std::pair<int, double> element : edge_in.param)
			{
				output<<"Parameter: "<<element.first<<" - Value: "<<element.second<<std::endl;
			}
			output<<"Calculated Weight:"<<edge_in.getWeight()<<std::endl;
			return output;
		}
		bool operator<(const Edge& edge_in) const
		{
			return getWeight() < edge_in.getWeight();
		}
		bool operator>(const Edge& edge_in) const
		{
			return getWeight() > edge_in.getWeight();
		}
		bool operator==(const Edge& edge_in) const
		{
			return getWeight() == edge_in.getWeight();
		}
		bool operator<=(const Edge& edge_in) const
		{
			return !(getWeight() > edge_in.getWeight());
		}
		bool operator>=(const Edge& edge_in) const
		{
			return !(getWeight() < edge_in.getWeight());
		}
		bool isSame(const Edge& edge_in) const
		{
			if(getWeight() == edge_in.getWeight()
				&& begining == edge_in.begining
				&& destination == edge_in.destination)
			{
				return true;
			}
			return false;
		}
};

#endif
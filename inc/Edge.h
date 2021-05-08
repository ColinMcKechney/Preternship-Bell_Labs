#ifndef EDGE_H
#define EDGE_H

#include "Node.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <unordered_map>

//Used to define the different newtwork slice types to identify which optimization method should be used
enum NetworkSliceType
{
	NoSlice = 0,
	Broadband = 1,
	LowLat = 2,
	Mach_to_mach = 3,
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

struct Node; //Preinitialize Node class since there's recursive definitions -- Will take this out and transfer it to int, as of now no need to store node pointers
struct Edge
{
	private:
		
		NetworkSliceType sliceType; //Identifies how the weight is calculated
		std::unordered_map<std::string, int> param; //Array of parameters to optimize the network slice
		double weight; //Stores the weight so it isn't recalculated upon calling each time
		
		//Default funciton for error catching
		double weight_NoSlice() const 
		{
			std::cout<<"No Slice Type Selected";
			return 0;
		}
		//Functions that calculate the weight of the edge, simplified for now
			//needs proper investigation once simulation is completed 
		double weight_Broadband() const
		{	
			return param.at("delay") + param.at("periodicity") + (param.at("throughput") ? 1.0/param.at("throughput") : 2) + (param.at("energy_eff") ? 1.0/param.at("energy_eff") : 2) + param.at("mission_crit_support") + (param.at("max_conn") ? 1.0/param.at("max_conn") : 2 ) + (param.at("packet_size") ? 1.0/param.at("packet_size") : 2) + (param.at("packet_loss")) + param.at("latency") + (param.at("reliability")) + (param.at("mobility") ? 1.0/param.at("mobility") : 2);
		}
		double weight_LowLat() const 
		{
			return param.at("delay") + (param.at("periodicity") ? 1.0/param.at("periodicity") : 2) + param.at("throughput") + param.at("energy_eff") +  (param.at("mission_crit_support") ? 1.0/param.at("mission_crit_support") : 2) + param.at("max_conn") + param.at("packet_size") + (param.at("packet_loss") ? 1.0/param.at("packet_loss") : 2) + (param.at("latency") ? 1.0/param.at("latency") : 2) + (param.at("reliability") ? 1.0/param.at("reliability") : 2) + param.at("mobility");
		}
		double weight_mach_to_mach() const {
			return (param.at("delay") ? 1.0/param.at("delay") : 2) + param.at("periodicity") + param.at("throughput") + param.at("energy_eff") + (param.at("mission_crit_support") ? 1.0/param.at("mission_crit_support") : 2) + param.at("max_conn") + param.at("packet_size") + (param.at("packet_loss") ? 1.0/param.at("packet_loss") : 2) + (param.at("latency") ? 1.0/param.at("latency") : 2) + param.at("reliability") + (param.at("mobility") ? 1.0/param.at("mobility") : 2);
		}
		
	public:
		Node* beginning; //Stores the endpoints of the edge, see above
		Node* destination;
		
		//Default Constructor
		Edge() : sliceType(NetworkSliceType::NoSlice), param(), weight(), beginning(NULL), destination(NULL) {}
		
		//Constructors, allowing for multiple overloads but upon implementation, one will be chosed
		Edge(const int type_in, const std::unordered_map<std::string, int> param_in, Node* start = NULL, Node* end = NULL) : sliceType((NetworkSliceType)type_in), param(param_in), weight(), beginning(start), destination(end) {getWeight(sliceType);}
		Edge(const NetworkSliceType type_in, const std::unordered_map<std::string, int> param_in, Node* start = NULL, Node* end = NULL) : sliceType(type_in), param(param_in), weight(), beginning(start), destination(end) {getWeight(sliceType);} //Prefered to use for implementation

		
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
				case NetworkSliceType::LowLat:
					weight = weight_LowLat();
					break;
				case NetworkSliceType::Mach_to_mach:
					weight = weight_mach_to_mach();
					break;
				case NetworkSliceType::NoSlice:
				default:
					weight = weight_NoSlice();
					break;
			}
			return weight;
		}

		double gettmpWeight(const NetworkSliceType type)const {
			switch(type)
			{
				case NetworkSliceType::Broadband:
					return weight_Broadband();
					break;
				case NetworkSliceType::LowLat:
					return weight_LowLat();
					break;
				case NetworkSliceType::Mach_to_mach:
					return weight_mach_to_mach();
					break;
				case NetworkSliceType::NoSlice:
				default:
					return weight_NoSlice();
					break;
			}
		}
		
		//Output overload
		friend std::ostream& operator<<(std::ostream& output, Edge& edge_in)
		{
			for(std::pair<std::string, int> element : edge_in.param)
			{
				output<<"Parameter: "<<element.first<<" - Value: "<<element.second<<std::endl;
			}
			output<<"Calculated Weight:"<<edge_in.getWeight()<<std::endl;
			return output;
		}
		//Overloaded operators
		bool operator<(const Edge& edge_in) const
		{
			return getWeight() < edge_in.gettmpWeight(this->sliceType);
		}
		bool operator>(const Edge& edge_in) const
		{
			return getWeight() > edge_in.gettmpWeight(this->sliceType);
		}
		bool operator==(const Edge& edge_in) const
		{
			return getWeight() == edge_in.gettmpWeight(this->sliceType);
		}
		bool operator<=(const Edge& edge_in) const
		{
			return !(getWeight() > edge_in.gettmpWeight(this->sliceType));
		}
		bool operator>=(const Edge& edge_in) const
		{
			return !(getWeight() < edge_in.gettmpWeight(this->sliceType));
		}
		//IsSame is used to identify exact same edges that aren't the same object, for unique edges in nodes
		bool isSame(const Edge& edge_in) const
		{
			if(getWeight() == edge_in.getWeight()
				&& beginning == edge_in.beginning
				&& destination == edge_in.destination)
			{
				return true;
			}
			return false;
		}
};

#endif
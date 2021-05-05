#ifndef NODE_H
#define NODE_H

#include <cstdlib>	
#include <iostream>



enum NetworkSliceType{ //Keep Consistency with edge.h

	NoSlice = 0,
	Broadband = 1,
	MissionCritical = 2,

};
template< class T >
struct node
{
	private:

		T     data;
		node* next;
		node* prev;
		int name; // labels which "edge cloud" it is
		int priority; // elaborates which network slice type it is
	public:

	
		node() : data(), next(NULL), prev(NULL), name(), priority() { }
	
		node(const T& dataIn, const int nameIn, const int priorityIn) : data(dataIn), next(NULL), prev(NULL), name(nameIn), priority(priorityIn) { }
	
		~node(){
			delete next;
		
	}
	

		node(const node<T>& copy) : data( copy.data ), next( NULL ), prev( NULL ), name(copy.name), priority(copy.priority) { }
	
	
		node<T>& operator=(const node<T>& assign){
		
			if(this != &assign){
				this->data = assign.data;
				this->next = NULL;
				this->prev = NULL;
			}
			return *this;
		}
	
	
		node<T>* operator=(const node<T>* assign){
		
			if(this != (void *)&assign){
				this->data = assign->data;
				this->next = NULL;
				this->prev = NULL;
			}
			return *this;
		}
	
	
		bool operator!=(const node<T>* rhs){
		
			return this != (void *)&rhs;
		
		}

		friend std::ostream& operator<<(std::ostream& output, node& nodeIn){
			output << "Data: "<< nodeIn.data<<"Name: "<<nodeIn.name<< " Priority: "<<nodeIn.priority<<std::endl;	
			return output;
		}
	
};



#endif

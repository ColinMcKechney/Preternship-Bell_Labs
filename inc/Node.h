#ifndef NODE_H
#define NODE_H

#include <cstdlib>	

template< class T >
struct node
{
	T     data;
	node* next;
	node* prev;
	
	node() : data(), next(NULL), prev(NULL) { }
	
	node(const T& dataIn) : data(dataIn), next(NULL), prev(NULL) { }
	
	~node(){
		
		delete next;
		
	}
	

	node(const node<T>& copy) : data( copy.data ), next( NULL ), prev( NULL ) { }
	
	
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
	
};



#endif

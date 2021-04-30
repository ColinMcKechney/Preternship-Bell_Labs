#include "../inc/Edge.h"

int main()
{
	Edge testEdge1;
	std::cout<<"\nTest 1: Default\n"<<testEdge1;
	double params2[] = {1,1,1,1};
	Edge testEdge2(1, params2);
	std::cout<<"\nTest 2: Broadband\n"<<testEdge2;
	double params3[] = {1,1,1,1};
	Edge testEdge3(2, params3);
	std::cout<<"\nTest 3: MC\n"<<testEdge3;
	double params4[] = {1,2,3,4};
	Edge testEdge4(2, params4);
	std::cout<<"\nTest 4: MC, Unique Parameters\n"<<testEdge4;
	std::cout<<"\nOperators working, test4 > test3: "<<(testEdge4 > testEdge3 ? "True" : "False")<<std::endl;
	std::cout<<"\nOperators working, test4 < test3: "<<(testEdge4 < testEdge3 ? "True" : "False")<<std::endl;
	std::cout<<"\nOperators working, test4 == test3: "<<(testEdge4 == testEdge3 ? "True" : "False")<<std::endl;
	std::cout<<"\nOperators working, test4 >= test3: "<<(testEdge4 >= testEdge3 ? "True" : "False")<<std::endl;
	std::cout<<"\nOperators working, test4 <= test3: "<<(testEdge4 <= testEdge3 ? "True" : "False")<<std::endl;
}
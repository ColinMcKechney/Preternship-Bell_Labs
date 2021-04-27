#include <nlohmann/json.hpp>
#include "../inc/Node.h"
//#include "inc/Edge.h"
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using json = nlohmann::json;



int main(int argc, char *argv[]){

    /*TODO:
    * Parse Command line arg (JSON file name)
    * Read in JSON
    * Create Nodes
    * Create Edges
    * Set Priorities
    * Run MST on all the nodes
    * Fork the MSTs
    */
   std::string json_name;
   for(int x=1; x<argc;x++){

       if(argv[x][0] == '-'){
           //flags entered here
           continue;
       }

       json_name = argv[x];

   }

   //get FILE * from json_name
   std::ifstream json_in(json_name);
   json j;
   json_in >> j;


    std::cout << j;



    
    
}
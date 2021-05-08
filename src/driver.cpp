#include <nlohmann/json.hpp>
#include "../inc/Node.h"
#include "../inc/Edge.h"
#include "../inc/Graph.h"
#include "../inc/Graphics.h"
#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <sstream>
#include <cstdlib>

using json = nlohmann::json;

std::string getSlice(int);

int main(int argc, char *argv[]){

    /*TODO:
    * Parse Command line arg (JSON file name)   - Incomplete
    * Read in JSON                              - Complete
    * Create Nodes                              - Complete
    * Create Edges                              - Complete
    * Set Priorities                            - Complete
    * Run MST on all the nodes                  - Incomplete 
    * Fork the MSTs                             - Incomplete
    */
   std::string json_name;
   json j;
   if(argc == 1)
        return 1;
   for(int x=1; x<argc && json_name.empty();x++){

       if(argv[x][0] == '-'){
           //flags entered here
           //unclear if we want flags anyway
           continue;
       }

       json_name = argv[x];
   }

   //get FILE * from json_name
   std::ifstream json_in(json_name);
   
   //read file into json
   json_in >> j;
   //close file
   json_in.close();


    //map that contains the different priority types by name
    std::unordered_map<std::string,std::unordered_map<std::string,int>> slice_types = j["priorities"].get<std::unordered_map<std::string,std::unordered_map<std::string,int>>>();


    Graph g; 
    //adding all the nodes to the graph
    for(std::unordered_map<std::string,int> n : j["nodes"].get<std::vector<std::unordered_map<std::string,int>>>()){
        g.addBlankNode({n["name"]}); //node needs  a section about what network slice it wants, should be added later
    }

    //adding all the edges to the graph
    for(std::unordered_map<std::string,int> e : j["edges"].get<std::vector<std::unordered_map<std::string,int>>>()){
        
        g.addEdge({e["slice_type"], slice_types[getSlice(e["slice_type"])], &g.verticies[e["source"]] , &g.verticies[e["destination"]]});

    } 
    std::cout << g << std::endl;
    
    //for testing purposes only

    //TODO run mst algorithm for each node
    int startNode =0;
    scanf("%d",&startNode);
    Window win;
    GC gc;
    Display *dis = create_window(win,gc);
    while(startNode >= 0 && startNode < g.vertexCount){ 
        Graph mst = g.MST(startNode);
        //draw_graph(dis,win,gc,mst);
        //hold_window(dis,win);
        //draw_graph(dis,win,gc,g);
        //hold_window(dis,win);
        std::cout << mst << std::endl; 
        scanf("%d",&startNode);  
    } 
    //close_window(dis,win,gc);
}

std::string getSlice(int slice){
    //returns the string version of the slice that we need
    //needed for the slice_types map
    switch(slice){
        case 1:
            return "mob_bband";
            break;
        case 2:
            return "rel_low_lat";
            break;
        case 3:
            return "mach_to_mach";
            break;
        default:
            return "NoSlice";
    }
}

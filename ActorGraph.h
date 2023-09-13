//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting Huang        A92091070
 *   Crystina Callahan  A13070475
 *   UCSD CSE100 staff
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include "BipartiteGraph.h"
#include <iostream>

// Maybe include some data structures here

using namespace std;


class ActorGraph {
protected:
  
    // Maybe add class data structure(s) here
    BipartiteGraph graph; 


public:
  //BipartiteGraph graph; 

    ActorGraph(void);

    // Maybe add some more methods here
  
    /** You can modify this method definition as you wish
     *
     * Load the graph from a tab-delimited file of actor->movie relationships.
     *
     * in_filename - input filename
     * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), 
     * otherwise all edge weights will be 1
     *
     * return true if file was loaded sucessfully, false otherwise
     */
    bool loadFromFile(const char* in_filename, bool use_weighted_edges);
  
  //function to relay the find path from BipartiteGraph
    string findPath(string fromKey, string toKey);

    //function to relay the find path from BipartiteGraph
    string findPathW(string fromKey, string toKey);

};


#endif // ACTORGRAPH_H

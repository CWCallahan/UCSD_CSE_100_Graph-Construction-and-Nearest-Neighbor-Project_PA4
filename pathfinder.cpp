//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting Huang    A92091070
 *   Crystina Callahan  A13070475
 */


#include "ActorGraph.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;

int main(int argc, char** argv) {
  
  if (argc != 5) return -1;
  string input    = argv[1];       //File containing actors/movies
  bool   weighted = *argv[2]-'u';   //Weighted or not
  string pairs    = argv[3];       //File with pairs to search for
  string output   = argv[4];       //Output file

  //Things we'll need:
  ActorGraph graph;
  ifstream   in;
  ofstream   out;
  in.open(pairs);
  out.open(output);

    
  //I.   BUILDING THE GRAPH
  //--------------------------------
  if (!graph.loadFromFile(argv[1], weighted)) return-1;

  //II.  Read the list of pairs
  //--------------------------------
 bool have_header = false;
 out << "(actor)--[movie#@year]-->(actor)--...\n"; 
 while (in){
 
      string s;
      // get the next line
      if (!getline( in, s )) break;                    
      if (!have_header) {
          // skip the header
          have_header = true;
          continue;
      }
      istringstream ss( s );
       vector <string> record;
       while(ss){
           string next;
           // get the next string before hitting a tab character and put it in 'next'
           if (!getline( ss, next, '\t' )) break;
           record.push_back( next );
       }
       if(record.size() != 2) continue;  
       string actor1( record[0] );
       string actor2( record[1] );

       //Now we make the connections
       if (weighted){
	 out << graph.findPathW(actor1,actor2);
       }
       else out << graph.findPath(actor1,actor2);
       
 }
 in.close(); 

  //we need to read in the pairs and call search on them as we read

  
}

//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting Huang    A92091070
 *   Crystina Callahan  A13070475
 */


#include "UnionFind.hpp"
#include "Movie.hpp"
#include <iostream>
#include <unordered_map>
#include <queue>
#include <utility>
#include <string>
#include <sstream>
#include <fstream>
#include "BipartiteGraph.h"

using namespace std;

class Compareto
{
public:
  bool operator() (pair<int,Movie*> p1, pair<int,Movie*> p2)
  {
    return p1.first>p2.first;
  }
};


int main(int argc, char** argv) {
  //Handle command-line input 
  //argc should be 5 or 4 depend on wheather the last argument is included
  string dataSet = argv[1]; // the file we need to open to make the graph 
  string pairs = argv[2];   //the pairs we need to test
  string output = argv[3];  //  the output file name
  string findType = "";
  if(argc == 5) findType = argv[4];

  bool ufind = true; //set to false only if argv[4] is bfs
  if(findType=="bst") ufind = false; 
   
  //first we need to read in all of the films and sort them by year 
  //This will require a hashmap of movies (will probably use the movie object)
  unordered_map< string, Movie* > movies;
  //as well as a priority queue
  priority_queue< pair<int, Movie*>,vector<pair<int,Movie*> >,Compareto > movieQ;
  UnionFind djSet;

  //use for bfs 
  priority_queue< pair<int, Movie*>,vector<pair<int,Movie*> >,Compareto > holderQ;
  BipartiteGraph graph;
  priority_queue< pair<int, Square*>,vector<pair<int,Square*> >,Compare2 > yearQholder;

  ofstream out;
  out.open(output);
  out<<"Actor1"<<'\t'<<"Actor2"<<'\t'<<"Year"<<"\n";
  //I.   READ THE INPUT / INITIALIZE STRUCTURES
  //-------------------------------------------------
  ifstream in;
  in.open(dataSet);
  bool have_header = false;
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
    if(record.size() != 3) continue;  
    string actor( record[0] );
    string movie_name( record[1]);
    int movie_year = stoi(record[2]);
    string key = movie_name+record[2];
    
    //check to use ufind or bfs 
    if(ufind){ 
      //check if the movie isn't in hash map
      if(movies.find(key)==movies.end()){
	//mke the movie obj
	Movie* newMovie = new Movie(movie_name,movie_year);
	//add it to the hash map 
	movies.insert(make_pair(key, newMovie));
	//add it to the queue
	movieQ.push(make_pair(movie_year,newMovie));
      }
      //look up the movie in the map and add the actor to it
      (movies.find(key)->second)->actors.push_back(actor);
    }
    else{ //if ufind false make the graph for bfs
      graph.connect(movie_name,movie_year,actor);
    }

  }//end of while
  if(!in.eof()) return -1;
  in.close();

  //II.  CHECK THE QUEUE YEAR BY YEAR
  //-------------------------------------------------
  // actor 1 and actor 2 should be read from file input at command line 
  //ifstream for reading in pairs of actors
  ifstream   inPair;
  //open the file containing pairs
  inPair.open(pairs);
  
  bool haveHeader = false;

  //loop through all the pairs 
  while(inPair){
    string str;
    // get the next line
    if (!getline( inPair, str )) break;
    if (!haveHeader) {
      // skip the header 
      haveHeader = true; continue;
    }   
    istringstream sss( str );
    vector <string> records;
    while(sss){
      string nxt;
      // get the next string before hitting a tab character and put it in 'next'
      if (!getline( sss, nxt, '\t' )) break;
      records.push_back( nxt );
    }   
    if(records.size() != 2) continue;
    string actor1( records[0] );
    string actor2( records[1] );
    //before we loop through to find the other actors we need to make our union set 
    //so we can still use the stuff we popped 
    //maybe make another priority Q to catch the stuff poped from out Q 
    //if that Q is not empty we pop all the stuff in it back to our Q befoe next round of search 

    if(ufind){
      while(holderQ.size()){
	movieQ.push(holderQ.top());
	holderQ.pop();
      }    
      //clear the djset 
      djSet.clearUnion();

      while(movieQ.size()){ //for all movies
	int year = movieQ.top().first;

	
	while( movieQ.top().first == year && movieQ.size()){ //and for all movies in that year
	  Movie* movie = movieQ.top().second;
	  //cout<<"year"<<movieQ.top().first<<endl;//we need to flip the priority of the Q
	  
	  for( int i=1; i<movie->actors.size(); i++){ //and for all actors in each film
	    djSet.unionOf(movie->actors[0],movie->actors[i]);  
	  }//END for actors
      
	  //holder that what movieQ poped
	  holderQ.push(movieQ.top());
	  movieQ.pop();
	}//END while for year        

	if ( (djSet.find(actor1)!=NULL) && (djSet.find(actor1)==djSet.find(actor2)) ){
	  out<<actor1<<'\t'<<actor2<<'\t'<<year<<"\n";
	  break;
	}

      }//END while for movieQ.size
      //this is the end of ufind specific actor connect 
      
    } else { //Now the bfs case

      //yearQholder is a recycling bin for removed years
      //  so we need to put those back onto our other movie priority queue
      //  even though its called year q and yearQholer these are actually ques of
      //  square objects which contain film that are sorted by year
      while(yearQholder.size()){ 
	graph.yearQ.push(yearQholder.top());
	yearQholder.pop();
      }
      
      //First lets turn off all of the films
      for(auto it = (graph.sqMap)->begin();it!=(graph.sqMap)->end();++it){
	it->second->exist = false;
      }

      //Now while the priority queue of films has any element 
      while(graph.yearQ.size()){
	int currYear = graph.yearQ.top().first;
	
        //cout<<graph.yearQ.top().second->name<<" "<<graph.yearQ.top().first <<endl; 
	graph.yearQ.top().second->exist = true;

	//reset graph to untouched state
        graph.clearBfs();
	
	vector<string> v = graph.findPath(actor1,actor2);
	
	for (int i=0; i<v.size(); i++) cout << v[i] << endl;
	if(v.size() >2 ){
          out<<actor1<<'\t'<<actor2<<'\t'<<currYear<<"\n";
          break;
	}
  	yearQholder.push(graph.yearQ.top());
        graph.yearQ.pop();
         
      }
    }
  }
  if(!inPair.eof()) return -1;
  inPair.close();

}

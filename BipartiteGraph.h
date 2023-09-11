//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting Huang        A92091070
 *   Crystina Callahan  A13070475
 */


#include "Circle.h"
#include "Square.h"
#include <queue>
#include <unordered_map>
#ifndef BIPARTATEGRAPH_H
#define BIPARTATEGRAPH_H

using namespace std;


class Compare
{
public:
    bool operator() (pair<int,Circle*> p1, pair<int,Circle*> p2)
    {
        return p1.first>p2.first;
    }
};

 class Compare2
  {   
      public: 
          bool operator() (pair<int,Square*> p1, pair<int,Square*> p2)
          {
              return p1.first>p2.first;
          } 
 };
class BipartiteGraph{

public:

//Constructor
BipartiteGraph();

//Destructor
~BipartiteGraph();

//Insert function for Square
void insert(string name, int year);

//Insert function for Circle
void insert(string name);

//Find function for Square
Square* findSquare(string name);

//Find function for Circle
Circle* findCircle(string name);

//Function to connect Square and Circle 
//try to find the square and cirle base on the parameter 
// if they exsist connect them else create them and connect them
void connect(string sqnName, int sqYear, string cName);

  //Size of the Bipartite Graph 
  int size();

  //print graph in bfs order   
  void printGraph(string key);

  /*a function to find the weighted shortest path from a node to another return a vector 
   * contain pais of circles and squares in order 
   */
  void dijkstra (string key);

  /*a function to find the shortest path from a node to another return a vector 
   * contain pais of circles and squares in order 
   */
  //vector<pair<Square*,Circle*>>
  void bfs (string key);

  /*a function to find the shortest path from a node to another return a vector 
   * contain pais of circles and squares in order 
   */
  vector<string> findPath(string fromKey, string toKey);

  //Gets the path in a string vector form using dijkstra
  vector<string> findPathW(string fromKey, string toKey);

  //clear status of bfs 
  void clearBfs();


  //Variables
  //Hash Map for Squares
  unordered_map<string, Square*>* sqMap;

  //size of sqMap
  int sSize;

  //Hash Map for Circles
  unordered_map<string, Circle*>* cMap;

  //size of cMap
  int cSize;

  //2D array for years 
  //or we can use a hash table -> direct hashing: key = 2015 - year 
  priority_queue< pair<int, Square*>,vector<pair<int,Square*> >,Compare2 > yearQ;


private: 
  //queue for bfs method
  queue< pair<Square*,Circle*> > q;

  //queue for bfs method
  priority_queue<pair <int,Circle*>, std::vector<pair<int,Circle*> >, Compare> pq;
  
  //helper method to go through the q 
  void traverseQ();

  //helper method for bfs to enqueue Squares into q (used for printing the graph)
  void enqCircle(Square* sq);

  //helper method for bfs to enqueue Circle into q (used for printing the graph)
  void enqSquare(Circle* c);

  //helper method for bfs to enqueue Circle into q (used for Dijkstra’s)
  void enqueuePQ(Circle* c);
  //helper method for bfs to enqueue Circle into q (used for Dijkstra’s)
  void enqueuePQ(Square* sq);

  //helper method for bfs to enqueue Circle into q (used for bfs)
  void enqueue(Circle* c);
  //helper method for bfs to enqueue Circle into q (used for bfs)
  void enqueue(Square* sq);

  
  };

#endif//BIPARTATEGRAPH_H

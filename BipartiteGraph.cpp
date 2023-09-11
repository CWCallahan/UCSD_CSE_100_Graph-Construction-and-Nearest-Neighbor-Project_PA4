//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting Huang        A92091070
 *   Crystina Callahan  A13070475
 */

#include "BipartiteGraph.h"
#include <iostream>
#include <queue>

using namespace std;

BipartiteGraph::BipartiteGraph(){
    sqMap = new unordered_map<string,Square*>();
    cMap  = new unordered_map<string, Circle*>();

}

void BipartiteGraph::insert(string name, int year){
    Square* s = new Square(name,year);
    sqMap->insert({s->name, s});
    sSize++;
}

void BipartiteGraph::insert(string name){
    Circle* c = new Circle(name);
    cMap->insert({c->name,c});
    cSize++;
}

void BipartiteGraph::connect(string sqName, int sqYear, string cName){
    string  y   = to_string(sqYear);
    string sqID = sqName+y;
    Square* sq  = findSquare(sqID); 
    Circle* c   = findCircle(cName);
    //find square 
    if(sq==NULL){
       //if it doesn't exist create it
       sq = new Square(sqName, sqYear);
       sq->ID = sqID;
       sqMap->insert({sqID, sq});
       sSize++;
       yearQ.push({sqYear,sq});
    }
    //find circle
    if(c== NULL){
       //if circle doesn't exist create it
       c = new Circle(cName);
       cMap->insert({c->name,c});
       cSize++;
    }
    
    //connecting sq with c 
    c->n->push_back(sq);
    sq->n->push_back(c);

}


Square* BipartiteGraph::findSquare(string name){ //need to take year most likely
     unordered_map<string,Square*>::const_iterator it; 
     it = sqMap->find(name);
     if ( it == sqMap->end() ) return NULL;
     else return it->second;
}

Circle* BipartiteGraph::findCircle(string name){
  unordered_map<string,Circle*>::const_iterator it;         
  it = cMap->find(name);
  if ( it == cMap->end() ) return NULL;
  else return it->second;
}

int BipartiteGraph::size(){
    return sSize+cSize;
}

void BipartiteGraph::printGraph(string key){
    //Pair obj for storing neighbors 
  Square* sq = findSquare(key);
    Circle* c = findCircle(key);

    if(sq){
        //insert sq as the origin into the q
        q.push({sq,NULL});
        traverseQ();
    }//end of if(sq)
    else if(c){
        q.push({NULL,c});
        traverseQ();
    }
}

void BipartiteGraph::traverseQ(){
    //while q is not empty 
    while(!q.empty()){
        //get the pair from queue 
        pair<Square*,Circle*> p = q.front();
        //pop the frint of q 
        q.pop();
        //check if its a circle or square
        if(p.first){
            //if first is not null it's a square
            Square* sq = p.first;
            //enqueue all of its circle neighbors to q
            enqCircle(sq);
        }//end of if
        else{
            //it's a circle
            Circle* c = p.second;
            //enqueue all of it's square neighbors to q
            enqSquare(c);
        }//end of else
    }//end of while
}

void BipartiteGraph::enqCircle(Square* sq){
  //check if sq have been visited 
  if(!sq->visited){
    //print out the square
    cout<<" "<<sq->name << endl;
    //if it's not visited enqueue all of the circle that's not visited 
    for(int i = 0; i < (*(sq->n)).size(); i++){
      if(!((*(sq->n))[i])->visited){
       	q.push({NULL,(*(sq->n))[i]});
      }
    }
    //set sq to visited 
    sq->visited = true;
  }
}

void BipartiteGraph::enqSquare(Circle* c){
  //check if c is visited
  if(!c->visited){
    //print out the circle
    cout<<" "<<c->name << endl;
    //if it's not visited enqueue all of the square that's not visited 
    for(int i = 0; i < (*(c->n)).size(); i++){
      if(!((*(c->n))[i])->visited){
	q.push({(*(c->n))[i],NULL});		
      }
    }       
    //set c to visited 
    c->visited = true;
  }                             
}


//DIJKSTRA 
void BipartiteGraph::dijkstra (string key){
    Circle* source = findCircle(key);
    //search for key for Circle
    if(!source) return;

    //I.   SET UP
    //--------------------------------
    while (!pq.empty()) pq.pop();        //ensure q is empty
    for ( auto it = cMap->begin(); it != cMap->end(); ++it) {
      it->second->dist= -1;	         //set dist to INFINITY (using unsigned int)
      it->second->prev= NULL;            //null pointer to previous
      it->second->visited= false;        //set visited to false
    }
    for ( auto it = sqMap->begin(); it != sqMap->end(); ++it) {
      it->second->dist= -1;	         //set dist to INFINITY (using unsigned int)
      it->second->prev= NULL;            //null pointer to previous
      it->second->visited= false;        //set visited to false
    }
      
    //II.  ADD AND MARK THE SOURCE
    //--------------------------------
    source->dist = 0;
    pq.push({0, source});

    //III. EXPLORE THE WHOLE GRAPH
    //--------------------------------
    while(!pq.empty()){
      //Get and pop the front of the queue
      Circle*  curr = pq.top().second;
      pq.pop();

      if (!curr->visited){
      	curr->visited = true;
      	//cout << "pq size:\t"<< pq.size() << endl;
	
	//also for all of these edges children  
	for(int i = 0; i < curr->n->size(); i++){        
	  for(int j = 0; j <  (*(curr->n))[i]->n->size(); j++){

	    Circle* neighbor =  (*(*(curr->n))[i]->n)[j];
	    Square* path     =  (*curr->n)[i];
	    int newDist      =  curr->dist+1+(2015-path->year);	    //(2016-(path->year));

	    if( curr == neighbor ) continue;        //skip the curr node 
	    else if( newDist < neighbor->dist) {    //if new dist < n.dist
	      //cout << newDist << '\t' << neighbor->dist << endl;
	      neighbor->dist = newDist;             //set its distance to the new
	      path->prev     = curr;                //set n's prev to curr
	      neighbor->prev = path;                //set n's prev to curr
	      neighbor->prev2 = curr;               //set n's prev to curr	    
		      
	      pq.push({ newDist, neighbor });       //enqueue the neighbor 
	    }
	  
	  }//END for II
	}//END for I
      }//END if Visited
    }//END while
}//END BFS

void BipartiteGraph::clearBfs(){
  for ( auto it = cMap->begin(); it != cMap->end(); ++it) {
    it->second->dist= -1;          //set dist to INFINITY (using unsigned int)
    it->second->prev= NULL;        //null pointer to previous
  }
  for ( auto it = sqMap->begin(); it != sqMap->end(); ++it) {
    it->second->dist= -1;          //set dist to INFINITY (using unsigned int)
    it->second->prev= NULL;        //null pointer to previous
  }
}

void BipartiteGraph::bfs (string key){
    Circle* source = findCircle(key);
    //search for key for Circle
    if(!source) return;
    
    //I.   SET UP
    //--------------------------------
    while (!q.empty()) q.pop();          //ensure q is empty
    for ( auto it = cMap->begin(); it != cMap->end(); ++it) {
      it->second->dist= -1;	         //set dist to INFINITY (using unsigned int)
      it->second->prev= NULL;            //null pointer to previous
    }
    for ( auto it = sqMap->begin(); it != sqMap->end(); ++it) {
      it->second->dist= -1;	         //set dist to INFINITY (using unsigned int)
      it->second->prev= NULL;            //null pointer to previous
    }
      
    //II.  ADD AND MARK THE SOURCE
    //--------------------------------
    source->dist = 0;
    q.push({NULL, source});

    //III. EXPLORE THE WHOLE GRAPH
    //--------------------------------
    while(!q.empty()){
      
      //Get and pop the front of the queue
      pair<Square*, Circle*> p = q.front();
      q.pop();
      //Enqueue the neighbors of the current node
      if(p.first)  enqueue(p.first);	    
      else         enqueue(p.second);
      
    }//END while
}//END BFS

void BipartiteGraph::enqueue(Square* cur){

  for(int i = 0; i < (*(cur->n)).size(); i++){     
    
    if( (*(cur->n))[i]->dist == -1 && cur->exist) { 	              // if n.dist == INFINITY:
      (*(cur->n))[i]->dist = cur->dist+1;             //set n.dist to curr.dist+1
      (*(cur->n))[i]->prev = cur;                     //set n's prev to curr
      q.push({ NULL, (*(cur->n))[i] });               //enqueue
    }     
  }
  //}//END if 
}// END enqueue

void BipartiteGraph::enqueue(Circle* cur){

  for(int i = 0; i < (*(cur->n)).size(); i++){        
    
    if( (*(cur->n))[i]->dist == -1 ) { 	              // if n.dist == INFINITY:
      (*(cur->n))[i]->dist = cur->dist+1;             //set n.dist to curr.dist+1
      (*(cur->n))[i]->prev = cur;                     //set n's prev to curr
      q.push({ (*(cur->n))[i],NULL });                //enqueue
    }

  }
}//END enqueue

//Gets the path in a string vector form using a bfs 
vector<string> BipartiteGraph::findPath(string fromKey, string toKey){
  
  vector<string> path;                                //We'll need a vector to store the path
  Circle* start = findCircle(fromKey);
  Circle* finish = findCircle(toKey);

  if(start==NULL || finish==NULL) return path;        //If either node doesn't exist exit
  else if(start->dist  != 0)  bfs(fromKey);           //Mark the nodes if not already done
  if(finish->dist == -1) return path;                 //Check for a connection       

  //Now we get the path
  Circle* cur = finish;
  path.insert(path.begin(),cur->name);

  while(path.front() != fromKey){
    
    path.insert(path.begin(),to_string(cur->prev->year));
    path.insert(path.begin(),cur->prev->name);        //add the prev to the string (square)
    path.insert(path.begin(),cur->prev->prev->name);  //add the prev prev to the string (circ)

    cur = cur->prev->prev;                            //now we are at the prev prev node
  }

  return path;
}//END findPath

//Gets the path in a string vector form using dijkstra 
vector<string> BipartiteGraph::findPathW(string fromKey, string toKey){
  vector<string> path;                                //We'll need a vector to store the path
  Circle* start  = findCircle(fromKey);
  Circle* finish = findCircle(toKey);


  if(start==NULL || finish==NULL) return path;        //If either node doesn't exist exit
  else if(start->dist  != 0) dijkstra(fromKey);       //Mark the nodes if not already done


  if(finish->dist == -1) return path;                 //Check for a connection       

  //Now we get the path
  Circle* cur = finish;
  path.insert(path.begin(),cur->name);
  
  while(path.front() != fromKey){
    path.insert(path.begin(),to_string(cur->prev->year));
    path.insert(path.begin(),cur->prev->name);        //add the prev to the string (square)
   
    path.insert(path.begin(),cur->prev2->name);  //add the prev prev to the string (circ)

  
    cur = cur->prev2;                            //now we are at the prev prev node

  }

  return path;
}//END findPath

BipartiteGraph::~BipartiteGraph(){}


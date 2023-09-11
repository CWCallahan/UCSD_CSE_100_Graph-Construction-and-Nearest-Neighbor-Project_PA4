//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting Huang    A92091070
 *   Crystina Callahan  A13070475
 */


//#include "UFNode.hpp"
#include <utility> 
#include <iostream>
#include <unordered_map>

#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP
using namespace std;

class UFNode{
public:
  UFNode(string name);
  ~UFNode();
  string name;      //Name of the actor
  UFNode* p;      //parent

};

UFNode::UFNode(string name)  {
  this->name = name;
  p = NULL;
}
  
UFNode::~UFNode(){}

class UnionFind{
public:
  UnionFind();
  ~UnionFind();
  
  //a map of all nodes based on name
  unordered_map<string, UFNode*> nodes;
  
  //a function to find
  UFNode* find(string s);
  
  //a function to union
  bool unionOf(string s1, string s2);
  void test();
  void clearUnion();
};


UnionFind::UnionFind(){}

UnionFind:: ~UnionFind(){
    for(auto it = nodes.begin(); it!=nodes.end();++it){
       delete(it->second);
    }
}

void UnionFind::clearUnion(){
    for(auto it = nodes.begin(); it!=nodes.end();++it){
      it->second->p = NULL;
    }
}

void UnionFind::test(){
  UFNode* N = new UFNode("test");

}


//a function to find
UFNode* UnionFind::find(string s){
    UFNode* curr = NULL;
  if(nodes.find(s)!=nodes.end()) curr = nodes.find(s)->second;
  if(curr) while(curr->p) curr = curr->p;
  return curr;   
}
 
//a function to union
bool UnionFind::unionOf(string s1, string s2){
  UFNode* n1 = find(s1);
  UFNode* n2 = find(s2);

  //retrieve the nodes or make them
  if (!n1){
    n1 = new UFNode(s1);     
    //nodes.insert( make_pair<string,Node*> (s1,n1) );   
    nodes.insert(make_pair(s1,n1) );
  }
  if (!n2){
    n2 = new UFNode(s2);     
    nodes.insert(make_pair(s2,n2) );   
  }

  if (n1==n2) return 0;
  //Otherwise we can join them up
  //compare to see which is deeper?
  //point the bottom of the smaller node to the top of the larger one
  //or maybe add this in later if neccesary

  UFNode* curr    = nodes.find(s2)->second;
  UFNode* newRoot = nodes.find(s1)->second;
  while (curr){
    UFNode* next = curr->p;
    curr->p      = newRoot;
    curr         = next;
  }

  //Now they've been joined so return true
   return true;
 }    


#endif //UNIONFIND_HPP

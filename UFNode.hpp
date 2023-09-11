//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting Huang    A92091070
 *   Crystina Callahan  A13070475
 */

#include <utility> 
#include <iostream>
#include <unordered_map>

#ifndef UFNODE_HPP
#define UFNODE_HPP
using namespace std;

class UFNode{
public:
  //Constructor 
  UFNode(string name);
  
  //Destructor 
  ~UFNode();

  //Name of the actor
  string name;

  //parent
  UFNode* p;
};

  UFNode(string name)  {
    this->name = name;
  }
  
  //Destructor 
~UFNode(){}
#endif//UNIONFIND_HPP

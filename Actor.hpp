/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting  Huang      A92091070
 *   Crystina   Callahan   A13070475
 */

#ifndef ACTOR_HPP
#define ACTOR_HPP

#include <vector>
#include <string>

using namespace std;

class Actor{
public:
    //Constructor 
  Actor(string name){
        this->name = name;
  }

    //Destructor 
    ~Actor();

    //Name of the actor
    string name; 

};
#endif//ACTOR_HPP

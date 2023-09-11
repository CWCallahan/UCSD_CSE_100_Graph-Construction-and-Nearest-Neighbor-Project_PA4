//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting  Huang      A92091070
 *   Crystina   Callahan   A13070475
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <string>
#include "Square.h"

using namespace std;

class Actor{
public:
    //constructor 
     Actor(string name);

    //destructor 
    ~Actor();

    //Variables
    //Name of the actor
    string name; 

};
#endif // CIRCLE_H

//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting Huang        A92091070
 *   Crystina Callahan  A13070475
 */

#ifndef CIRCLE_H
#define CIRCLE_H

#include <vector>
#include <string>
class Square;
#include "Square.h"

using namespace std;

class Circle{

public:
    //constructor 
     Circle(string name);

    //destructor 
    ~Circle();

    //variables

    //Name of obj
    string name; 
    
    //vector to all square neighbors 
    vector<Square*>* n;
    
    //bool value keeping tract of if its visited or not 
    bool visited;

    //pointer used for finding shortest path 
    Square* prev;

    //pointer used for finding shortest path 
    Circle* prev2;

     //distance variable for finding te shortest path
    unsigned int dist;

};
#endif // CIRCLE_H

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
using namespace std;

Circle::Circle(string name){
    this->name  = name;
    visited     = false;
    n           = new vector<Square*>;
    prev        = NULL;
    dist        = -1;
}

Circle::~Circle(){
   delete(n);
}

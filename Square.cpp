//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting Huang        A92091070
 *   Crystina Callahan  A13070475
 *   UCSD CSE100 staff
 */

#include "Circle.h"
#include "Square.h"
using namespace std;


Square::Square(string name, int year){
   this->name  = name;
   this->year  = year;
   n           = new vector<Circle*>;
   exist       = true;
   visited     = false;
   prev        = NULL;
   dist        = -1;
}
Square::~Square(){
  delete(n);
}






//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting Huang        A92091070
 *   Crystina Callahan  A13070475
 *   UCSD CSE100 staff
 */

#ifndef SQUARE_H
#define SQUARE_H

#include <vector>
#include <string>
class Circle;
#include "Circle.h" 
 
using namespace std;
  
class Square{
public:
  //constructor 
  Square(string name, int year);             
  //destructor 
  ~Square();
                                  
  //variables
                                            
  //Name of obj
  string name;

  //an ID that distinguishes between object with the same name but different weight
  string ID;

  //int for year
  int year; 

  //vector to all square neighbors 
  vector<Circle*>* n;
                                                                          
  //bool value keeping tract of if its visited or not 
  bool visited, exist;
                                                                                    
  //pointer used for finding shortest path
  Circle* prev;

  //distance variable for finding te shortest path
  unsigned int dist;
                                                                                     
                                                                                      
};
                

#endif // SQUARE_H

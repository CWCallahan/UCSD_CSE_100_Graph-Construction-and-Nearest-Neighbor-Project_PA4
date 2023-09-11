//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA4 C++ Graph
 *  A class representing a protein sequence 
 *  Authors: 
 *   Shih-Ting Huang    A92091070
 *   Crystina Callahan  A13070475
 */

#ifndef TRAIT_H
#define TRAIT_H

#include <iostream>
#include <string>
#include <vector>
class    Protein;
#include "Protein.h"

using namespace std;

class Trait{
public:
  //functions:
  Trait(string name, double value);
  ~Trait();
  void makeHistogram();

  //variables:
  vector<Protein*> proteins;
  string           name;
  int              value;
  
private:

 
};
#endif//TRAIT_H





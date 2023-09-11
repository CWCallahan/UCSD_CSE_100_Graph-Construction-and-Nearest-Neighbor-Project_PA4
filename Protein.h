//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA4 C++ Graph
 *  A class representing a protein sequence 
 *  Authors: 
 *   Shih-Ting Huang    A92091070
 *   Crystina Callahan  A13070475
 */

#ifndef PROTEIN_H
#define PROTEIN_H

#include <iostream>
#include <string>
#include <vector>
class    Trait;
#include "Trait.h"
using namespace std;

class Protein{
public:
 
  //Functions:
  Protein(string name, string sequence);
  ~Protein();

  //Variables:
  int size;
  vector<Trait*> traits;
  string name;
  
private:
  //Functions:
  void characterize();
  
  //Variables
  string sequence;
  
};
#endif//PROTEIN_H



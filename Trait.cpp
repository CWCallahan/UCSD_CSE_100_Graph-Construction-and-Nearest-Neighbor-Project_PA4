//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA4 C++ Graph
 *  A class representing a protein sequence 
 *  Authors: 
 *   Shih-Ting Huang    A92091070
 *   Crystina Callahan  A13070475
 */


#include "Trait.h"
using namespace std;

Trait::Trait(string name, double value){
  this->name  = name;
  this->value = value;
}

Trait::~Trait(){}




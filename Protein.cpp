//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA4 C++ Graph
 *  A class representing a protein sequence 
 *  Authors: 
 *   Shih-Ting Huang    A92091070
 *   Crystina Callahan  A13070475
 */

#include "Protein.h"
using namespace std;

Protein::Protein(string name, string sequence){
  this->name     = name;
  this->sequence = sequence;
  size = sequence.length();
  characterize();
}

Protein::~Protein(){}

void Protein::characterize() {
  //characterize size
  size = sequence.length() ;
  if (size < 10) ;
  //characterize ph 
}

 




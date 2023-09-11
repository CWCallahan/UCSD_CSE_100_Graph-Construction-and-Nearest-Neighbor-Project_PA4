/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting  Huang      A92091070
 *   Crystina   Callahan   A13070475
 */

#ifndef MOVIE_HPP
#define MOVIE_HPP

#include <vector>
#include <string>

using namespace std;

class Movie{
public:
    //Constructor 
  Movie(string name, int year){
    this->name = name;
    this->year = year;
  }

    //Destructor 
    ~Movie();

    //Name of the film
    string name; 

    //Year of the film
    int year;

  //add a vector of strings (for actors)
  vector<string> actors;
};
#endif // MOVIE_HPP

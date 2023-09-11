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
#include "ActorGraph.h"
//#include "UnionFind.hpp"
#include <iostream>
#include <unordered_map>

using namespace std;

int main(int argc, char** argv) {
   // make a node 
   Circle* c = new Circle("CHiKENtigaMAsara");
   Square* s = new Square("lol",1996);
   c->n->push_back(s);
   s->n->push_back(c);
   cout<<((*(c->n))[0])->name <<endl;
   cout<<((*(s->n))[0])->name<<endl;
   cout<<((*(c->n))[0])->year<<endl;


  // delete(s);
  // delete(c);
   cout << "hiiii" << endl;

   unordered_map<string,Circle*> cMap;
   cMap.insert({c->name,c});
   for(auto& x:cMap)
       cout<< x.first << ":" << (x.second)->name<<endl;

   BipartiteGraph b;
   BipartiteGraph* bg = new BipartiteGraph();
   cout<<"before "<<bg->size()<<endl;
   bg->insert("noodle", 20);//square
   bg->insert("killBill");//circle 
   cout<<"after "<<bg->size()<<endl;
   bg->connect("noodle",20,"killBill");
   cout<<"after connect: "<<bg->size()<<endl;
   Square* found = bg->findSquare("noodle");
   bg->connect("Umami",10,"killBill");
   bg->connect("noodle",20,"sashimi");
   bg->connect("wasabi",20,"sashimi");
   bg->connect("Umami",20,"TOMATO");
   //bg->connect("noodle",20,"TOMATO");
   bg->printGraph("killBill");

   unsigned int infinity = -1;
   if (infinity == -1) cout << "this does work" << endl;
   else cout << "this doesnt work" << endl;
   cout << "inf:\t" << infinity << endl;

   cout << "Testing the bfs" << endl;
   bg->bfs("killBill");
   cout << "finished testing" << endl;

   cout << "Testing findPath " << endl;
   bg->findPath("killBill","TOMATO");
   for (auto const& word: bg->findPath("killBill","TOMATO") )
     cout << "\t" << word << endl;
/*
   //Testing the ActorGraph Class
   cout << endl << "Testing the ActorGraph Class"  << endl;
   ActorGraph ag;
   cout << "First attempting to read data from file" << endl;
   ag.loadFromFile("movie_casts.tsv", 0);
   cout << "Done loading the file" << endl;
   cout << ag.findPath("50 CENT","ABDOO, ROSE");
   cout << ag.findPathW("50 CENT","ABDOO, ROSE");

   //for (auto const& word: ag.findPath("50 CENT","ABDOO, ROSE") )
   //cout << "\t" << word << endl; 
						       
   //Lets test the Dijkstra
   //------------------------------------
   ActorGraph *ag2;
   cout << "1" << endl;

   ag2->graph.connect("kara",2001,"killBillI");
   ag2->graph.connect("jessica",2001,"killBillI");
   cout << "1" << endl;
   ag2->graph.connect("kara",2015,"killBillII");
   ag2->graph.connect("daisy",2015,"killBillII");
   cout << "2" << endl;
   ag2->graph.connect("jessica",1000,"shehulk");
   ag2->graph.connect("daisy",1000,"shehulk");
   //now lets check the path
   cout << "3" << endl;

   cout << ag2->findPath("jessica","daisy");
*/
   bool weight ='u'- 'u';
   cout<< "weight " << weight <<endl;
   
   delete(bg);
   delete(c);
   delete(s);


   //Alright! Time to test UnionFind
   // UnionFind* uf = new UnionFind;
   //cout << uf->find("A") << endl;
   //cout << uf->find("B") << endl;
}

//-*- mode: linum; mode: c++ -*-
/**
 *  CSE 100 PA3 C++ Graph
 *  A class for the graph
 *  Authors: 
 *   Shih-Ting Huang    A92091070
 *   Crystina Callahan  A13070475
 */


#include <iostream>
#include <fstream>
#include <cmath>
#include "Trait.h"
#include "Protein.h"

using namespace std;

void readNewProtein(vector<Trait*> &sizes,
		    vector< pair< string,vector<Protein*> > > &categories) {
  string category;
  string inFile;
  string line, name, sequence;
  vector<Protein*> proteinsRead;
  
  //Read in the File and category name 
  //----------------------------------
  cout << "Please enter the name of this category:" << endl;
  cin  >> category;
  cout << "Please provide a .FASTA file format" << endl
       << "The file can contain multiple proteins but all" 
       << " should belong to a specific category." << endl;
  cin  >> inFile;
  cout << "loading the proteins into the graph..." << endl;

  std::ifstream in(inFile);
  //INTRODUCE CHECKS

  while ( getline(in,line) ){
    //if the line is a '>' then we are at a name and we can record it 
    if( line[0] == '>' ){
      name = line.substr(1); //check this out/change
      cout << name << endl;
    }
    while( !line.empty() ){
      sequence += line;
      getline(in,line);
    }
    cout << "\nname:\t" << name << '\n' << sequence << endl;

    //else if the line is not empty then we can add to the string
    //if the line is empty just keep reading 

    //Create the new protein object
    Protein* p = new Protein(name, sequence);
    proteinsRead.push_back(p);
    
    //Here we can interpret the results 
    //----------------------------------
    //record size by assigning assigning it in the size vecor of trait edge/nodes
    int sizeKey = p->size/100;                   //key corresponding to size bin
    if (sizeKey>10) sizeKey = 10;
    sizes[sizeKey]->proteins.push_back(p);
    p->traits.push_back(sizes[sizeKey]);

    //we can add up all amino acids of a certain type to determine acidic character

    //We can also set the individual profile here!
    //----------------------------------
    
    name.clear();
    sequence.clear();
  }

  //Establish the Category  
  //----------------------------------
  categories.push_back(make_pair(category,proteinsRead));   
}

void predict(vector<Trait*> &sizes,
	     vector< pair< string,vector<Protein*> > > &categories ){
  string inFile;
  string line, name, sequence;
  Protein* p;
  int sizeKey;
  
  //First we need to get in the next protein from a FASTA file 
  //----------------------------------
  cout << "Please enter the name of the file:" << endl;
  cout << "Note: it should only contain one protein this time." << endl;
  cout << "If more than one is included then only the first will be read." << endl;
  cin  >> inFile; 
  std::ifstream in(inFile);

  if( getline(in,line) ){ //change to if 
    if( line[0] == '>' ){    //if the line is a '>' then we are at a name,  record it 
      name = line.substr(1); //check this out/change
      cout << name << endl;
    }
    
    while( !line.empty() ){
      sequence += line;
      getline(in,line);
    }
    cout << "\nname:\t" << name << '\n' << sequence << endl;

    //Create the new protein object
    //----------------------------------
    p = new Protein(name, sequence);
    
    //Here we can interpret the results 
    //----------------------------------
    //Record size by assigning  it in the size vecor of trait edge/nodes
    sizeKey = p->size/100;                   //key corresponding to size bin
    if (sizeKey>10) sizeKey = 10;
    sizes[sizeKey]->proteins.push_back(p);
    p->traits.push_back(sizes[sizeKey]);
    
    //we can add up all amino acids of a certain type to determine acidic character

  }

  //Now let's get the profiles for the categories
  //----------------------------------

  //for each category
  //and for each trait group in that category
  //record the expeceted value at each index

  //we need an array that we increment for each protein and each trait type
  vector<double> sizeProfile (11,0);
  //add other profiles as other traits are added

  //We'll need a vector that mirrors the Categories vector so it can store
  //  the scores
  vector<double> scores (categories.size(),0);
  double sum = 0; //We need this to normalize later

  for (int i=0;i<categories.size();i++){ 

    //Step I.   Use the profile vectors count trait distribution
    //----------------------------------
    for (int j=0; j<categories[i].second.size(); j++){

      cout << "protein:\t\t" <<  categories[i].second[j]->name << endl;
      cout << "traits[0]->name\t\t" <<  categories[i].second[j]->traits[0]->name << endl;
      cout << "traits[0]->value\t" <<  categories[i].second[j]->traits[0]->value << endl;
      //categories second is the vec of proteins in that cat
      int sizeHit = categories[i].second[j]->traits[0]->value;
      cout << "sizeHit\t\t" << sizeHit << endl;
      sizeProfile[sizeHit] ++; //increment this bin
      cout << "sizeProfile[sizeHit]\t" << sizeProfile[sizeHit] << endl;
      sum ++;
    }

    //Step II.  Now we need to nomalize this to one
    //----------------------------------
    for (int j=0; j<sizeProfile.size(); j++) sizeProfile[j]/=sum;
    
    //Step III. We also need the profile for the new protein
    //----------------------------------
    //  However it is automatically normalized so we can just
    //  directly get the score.
    sizeProfile[sizeKey]--; 
    for (int j=0; j<sizeProfile.size(); j++)
      scores[i] += abs(sizeProfile[j]);
    //That may have been hard to follow so to restate
    //  we subtracted the two distributions from each other and
    //  took the abs value, meaning that we'll get a score for size
    //  between 0 and 2, where 0 means 100% match, and 2 means no match
    //Lets make this easier to read by normalizing to one and flipping
    scores[i] = 1-scores[i]/2; 
    //essentially this score is now a measure of distribution overlap or %match
    //0, no overlap and 1, same distribution

    //Step IV.  Generate the data
    //----------------------------------
    for (int j=0; j<sizeProfile.size(); j++)
      cout << "sizeProfile\t" << sizeProfile[j] << endl;
    cout << "Scores for category: " << categories[i].first << endl;
    cout << '\t' << "Size: \t";
    cout << scores[i] << endl;   

    //Step V.  Reset the sensitve variables
    //----------------------------------
    for (int j=0; j<sizeProfile.size(); j++) sizeProfile[j]=0;
    sum = 0;
    
  }//end categories loop
}


int main( int argc, char **argv ){
  //Some variables and structures to use later
  //  Categories of proteins determined by the user input
  vector< pair< string,vector<Protein*> > > categories;
  vector<Trait*> sizes;                //A group of size traits
  vector<Trait*> pkas;                 //A Group of pka traits
  char           choice  = 0;          //a char for console input
  bool           running = true;       //Denotes if the program should be running

  //First lets establish the trait nodes
  //----------------------------------
  //  Size Nodes
  Trait* size0_100     = new Trait("Size: 0-100"   ,0);
  Trait* size100_200   = new Trait("Size: 100-200" ,1);
  Trait* size200_300   = new Trait("Size: 200-300" ,2);
  Trait* size300_400   = new Trait("Size: 300-400" ,3);
  Trait* size400_500   = new Trait("Size: 400-500" ,4);
  Trait* size500_600   = new Trait("Size: 500-600" ,5);
  Trait* size600_700   = new Trait("Size: 600-700" ,6);
  Trait* size700_800   = new Trait("Size: 700-800" ,7);
  Trait* size800_900   = new Trait("Size: 800-900" ,8);
  Trait* size900_1000  = new Trait("Size: 900-1000",9);
  Trait* size1000plus  = new Trait("Size: 1000+"   ,10);

  //Maintaining similar trait nodes in a vector will make
  //   histogram building easier later on
  sizes.push_back(size0_100);
  sizes.push_back(size100_200);
  sizes.push_back(size200_300);
  sizes.push_back(size300_400);
  sizes.push_back(size400_500);
  sizes.push_back(size500_600);
  sizes.push_back(size600_700);
  sizes.push_back(size700_800);
  sizes.push_back(size800_900);
  sizes.push_back(size900_1000);
  sizes.push_back(size1000plus);

  //Add other trait nodes later(pka)
 
  //Now that the initial graph set up is complete we can
  //  prompt the user for choices
  //----------------------------------
  cout << "This tool will allow you to categorize proteins and based on user input.\n"
       << "Additionally, You can also generate histograms of certain traits \n"
       << "and utilize some graph traversal to see similar proteins by different degree"
       << endl;
  do{
    cout << "\t\'n\'\t to begin by reading a new data set." << endl;
    cout << "\t\'p\'\t to predict protein category." << endl;
    cout << "\t\'d\'\t to get data." << endl;
    cout << "\t\'s\'\t to get neighbors/similar proteins." << endl;
    cout << "\t\'e\'\t to exit." << endl;
    cin >> choice;
    switch (choice) {
    case 'n': readNewProtein(sizes, categories); break;
    case 'p': predict(sizes, categories); break;
    case 'd': break;
    case 's': break;
    case 'e': running = false; break;
    }
  }while(running);


   
  return 0;
}

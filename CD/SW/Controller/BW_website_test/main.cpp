// Project		Exercises 4. Semester projekt
//
// File			Website.hpp
//
// Description	Implementation of class website - main test program
//
// Author		Jeppe Hofni
//
// Version		1.0 - 01052015

#include <stdio.h>
#include <iostream>
#include "Website.h"
#include <fstream>

using namespace std;



int main()
{
  Website BabyWatch;
  
  char choice = 'q';
  cout << ">>Main Program for testing Class Website<<\n\n " << endl;
  
  while(true)
  {
	  cout << "Please write '1','2' or '3' for different BabyCon levels, q for quit " << endl;
	  
	  cin >> choice;
	  
	  if(choice == '1' || choice == '2' || choice == '3')
	  {
	  
		  switch ( choice ) 
		  {
		  case '1':
		  	BabyWatch.updateToBabyCon1();
		  	break;
		  
		  case '2':
		  	BabyWatch.updateToBabyCon2();
		  	break;
		  
		  case '3':
		  	BabyWatch.updateToBabyCon3();
		  	break;
			
		  default:
		  	cout << "Error in BabyCon assignment\n" << endl;
		  	break;
		  }
	
	  }
	  else if( choice == 'q')
	  {
		
		return 0;
	  }
	  else
	  {
	    cout << "Please try agian...\n" << endl; 
	  }
  }
	  
  return 0;
}
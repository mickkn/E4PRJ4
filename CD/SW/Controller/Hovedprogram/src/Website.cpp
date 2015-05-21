// Project		Exercises 4. Semester projekt
//
// File			Website.hpp
//
// Description	Implementation of class website
//
// Author		Jeppe Hofni
//
// Other		Mick Kirkegaard
//
// Version		1.0 - 01052015

#include "Website.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;


Website::Website()
{
	initWebsite();
}

Website::~Website()
{
	stopWebsite();
}

void Website::initWebsite()
{
  //cout << "init website\n" << endl;
  
  system("/root/Flask/flask.sh");
  updateToBabyCon3();
}

void Website::stopWebsite()
{
  //cout << "stop website\n" << endl;
  system("/root/Flask/killpython.sh");
}

void Website::updateToBabyCon1()
{
  //cout << "BabyCon1\n" << endl;
  updateFile(1);
  
}

void Website::updateToBabyCon2()
{
  //cout << "BabyCon2\n" << endl;
  updateFile(2);
}

void Website::updateToBabyCon3()
{
  //cout << "BabyCon3\n" << endl;
  updateFile(3);
}

void Website::updateFile( int BCon)
{
  string babyConString;
  
  // Write text file
  FILE * txtFile;
  txtFile = fopen ("/root/Flask/static/tilstand.txt","wb");
  if (txtFile==NULL)
  {
    cout << "Could not write text file\n" << endl;
  }
  
  // Switch Case to set filepath
  switch ( BCon ) 
  {
  case 1:
  	babyConString = "/root/Flask/static/BabyCon1.JPG";
  	fputs ("Adam Alarm! E-mail sendt",txtFile);
  	break;
  
  case 2:
  	babyConString = "/root/Flask/static/BabyCon2.JPG";
  	fputs ("Adam er urolig!",txtFile);
  	break;
  
  case 3:
  	babyConString = "/root/Flask/static/BabyCon3.JPG";
  	fputs ("Adam er rolig",txtFile);
  	break;
  
  default:
  	cout << "Error in BabyCon assignment\n" << endl;
  	break;
  }
  
  const char * BCptr_ = babyConString.c_str();
  fclose (txtFile);
  
  
  // Read Picture file
  FILE * readFile;
  FILE * writeFile;
  
  long lSize;
  char * buffer;
  size_t result;
  
  readFile = fopen (BCptr_,"rb");
  if (readFile == NULL)
  {
      cout << "Could not picture read file\n" << endl;
  }
  
   // obtain file size:
  fseek (readFile , 0 , SEEK_END);
  lSize = ftell (readFile);
  rewind (readFile);

  // allocate memory to contain the whole file:
  buffer = (char*) malloc (sizeof(char)*lSize);
  
  if (buffer == NULL)
  {
    cout << "Memory error when creating Website buffer\n" << endl;
  }

  // copy the file into the buffer:
  result = fread (buffer,1,lSize,readFile);
  if (result != lSize)
  {
    cout << "Reading error\n" << endl;
  }

  /* the whole file is now loaded in the memory buffer. */

  
  // Write picture file
  
  writeFile = fopen ("/root/Flask/static/BabyCon.JPG","wb");
  
  if (writeFile == NULL)
  {
      cout << "Could not write picture file\n" << endl;
  }
  
  
  fwrite (buffer , sizeof(char), lSize, writeFile);
  
  
  // Close files
  fclose (readFile);
  fclose (writeFile);
  
  // free memory
  
  free (buffer);
  
  
}

// Project		Exercises 4. Semester projekt
//
// File			Website.hpp
//
// Description	Implementation of class website
//
// Author		Jeppe Hofni
//
// Version		1.0 - 01052015

#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;


class Website
{
public:
  Website();
  ~Website();
  void initWebsite();
  void stopWebsite();
  void updateToBabyCon1();
  void updateToBabyCon2();
  void updateToBabyCon3();
private:
  void updateFile( int BCon);
  // dummy
};



// +---------------------------------------------------------------------------+
// | MM7DTest v0.1 * Tester program for MM7D air quality measuring device      |
// | Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>           |
// | t_modbus.cpp                                                              |
// | Tester for Modbus                                                         |
// +---------------------------------------------------------------------------+

//   This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License 3.0 version.
//
//   This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.

#include <conio.h>
#include <dos.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "messages.h"
#include "utils.h"

using namespace std;

#define    MODBUSGETPROG  ""
#define    TEMPFILE     "mm7dtest.tmp"

// write header with menu
void mheaderwithmenu(int menu)
{
  cls();
  cout << "Ú";  for (int i = 0; i < 77; i++) cout << "Ä"; cout << "¿";
  cout << "\n";
  cout << msg(0) << msg(1);
  cout << "À";  for (int i = 0; i < 77; i++) cout << "Ä"; cout << "Ù"; cout << "\n";
  if (menu == 0)
  {
    cout << msg(29);
    for (int i = 5; i < 10; i++)
       cout <<"\tF" << i-4 << ":\t" << msg(i+7) <<"\n";
    cout <<"\tF6:\t" << msg(14+7) <<"\n";
    cout << msg(10);
  } else cout << "\n" << msg(menu+11) << ":\n\n";
}

// get information about device
void mf1(char *ip)
{
  pause(27);
}

// get all measured data
void mf2(char *ip)
{
  pause(27);
}

// get measured temperature
void mf3(char *ip)
{
  pause(27);
}

// get measured relative humidity
void mf4(char *ip)
{
  pause(27);
}

// get measured relative unwanted gas level
void mf5(char *ip)
{
  pause(27);
}

// set limit values and get all measured data
void mf6(char *ip)
{
  pause(27);
}

// main function
void modbustest(char *ip)
{
  // menu
  mheaderwithmenu(0);
  bool repeat = true;
  char ch;
  while (repeat)
  {
    if (kbhit())
    {
      ch = getch();
      if (ch == 0)
      {
        ch = getch();
        switch (ch)
        {
          case 59:
            mf1(ip);
            mheaderwithmenu(0);
            break;
          case 60:
            mf2(ip);
            mheaderwithmenu(0);
            break;
          case 61:
            mf3(ip);
            mheaderwithmenu(0);
            break;
          case 62:
            mf4(ip);
            mheaderwithmenu(0);
            break;
          case 63:
            mf5(ip);
            mheaderwithmenu(0);
            break;
          case 64:
            mf6(ip);
            mheaderwithmenu(0);
            break;
        }
      }
      if (ch == 27) repeat = false;
    }
  }
}

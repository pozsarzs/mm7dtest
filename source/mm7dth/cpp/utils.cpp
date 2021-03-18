// +---------------------------------------------------------------------------+
// | MM7DTest v0.1 * Tester program for MM7D air quality measuring device      |
// | Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>           |
// | utils.cpp                                                                 |
// | Utilities                                                                 |
// +---------------------------------------------------------------------------+

//   This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License 3.0 version.
//
//   This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.

#include <conio.h>
#include <stdlib.h>
#include <dos.h>
#include <iostream>

using namespace std;

// clear screen
void cls()
{
  system("cls");
}

// pause until keypress
void pause(int scancode, char const *message)
{
  cout << message;
  bool repeat = true;
  char ch;
  while (repeat)
  {
    if (kbhit())
    {
      if (ch == 0)
      {
        ch = getch();
        cout << ch;
        if (ch == scancode) repeat = false;
      } else
      {
        ch = getch();
        if (ch == scancode) repeat = false;
      }
    }
  }
}

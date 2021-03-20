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
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// clear screen
void cls()
{
#ifdef __MSDOS_
  system("cls");
#else
  system("clear");
#endif
}

// pause until keypress
void pause(int scancode, char const *message)
{
  printf("%s\n",message);
  bool repeat = true;
  char ch;
  while (repeat)
  {
    if (kbhit())
    {
      ch = getch();
      if (ch == 0) ch = getch();
      if (ch == scancode) repeat = false;
    }
  }
}

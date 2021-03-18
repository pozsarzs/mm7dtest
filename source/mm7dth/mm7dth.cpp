// +---------------------------------------------------------------------------+
// | MM7DTest v0.1 * Tester program for MM7D air quality measuring device      |
// | Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>           |
// | mm7dth.cpp                                                                |
// | Program for DOS                                                           |
// +---------------------------------------------------------------------------+

//   This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License 3.0 version.
//
//   This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.

// Exit codes:
// 0: normal exit
// 1: bad IP address in command line parameter

#include <conio.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "ipcheck.h"
#include "messages.h"
#include "t_http.h"
#include "utils.h"

#define    PRGNAME      "MM7DTest"
#define    PRGVER       "v0.1"

using namespace std;

int main(int argc, char *argv[])
{
  int rc = 0;
  // no argument
  if (argc != 3)
  {
    if (argc == 2)
    {
      // usage screen
      if ((std::string(argv[1]) == "-h") || (std::string(argv[1]) == "--help"))
      {
        cout << msg(2);
        return (0);
      } else
      {
      // name and version
        if ((std::string(argv[1]) == "-v") || (std::string(argv[1]) == "--version"))
        {
          cout << PRGNAME << " " << PRGVER << "\n";
          return (0);
        } else
        {
          cout << msg(2);
          return (0);
        }
      }
    } else
    {
      cout << msg(2);
      return (0);
    }
  } else
  {
    // check IP address
    char *ipaddress;
    strcpy(ipaddress,argv[1]);
    if (validate_ip(ipaddress) != 1)
    {
      cerr << msg(3);
      rc = 1;
    } else
    {
      // normal start
      strcpy(ipaddress,argv[1]);
      char *uid;
      uid = argv[2];
      httptest(ipaddress,uid);
      cls();
    }
  }
  return rc;
}
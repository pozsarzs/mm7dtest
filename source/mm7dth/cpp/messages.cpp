// +---------------------------------------------------------------------------+
// | MM7DTest v0.1 * Tester program for MM7D air quality measuring device      |
// | Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>           |
// | messages.cpp                                                              |
// | Messages                                                                  |
// +---------------------------------------------------------------------------+

//   This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License 3.0 version.
//
//   This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.

// get message
char const *msg(int const index)
{
  static char const * const message[] =
  {
    /*  0 */  "| MM7DTest v0.1 * Tester program for MM7D air quality measuring device        |\n",
    /*  1 */  "| Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>             |\n",
    /*  2 */  "Usage:\n\tmm7dtest.exe IP_address UID\n\n",
    /*  3 */  "Bad IP address!\n",
    /*  4 */  "IP address: ",
    /*  5 */  "\nMenu:\n\n",
    /*  6 */  "\tThe automatic mode is set.\n",
    /*  7 */  "\tThe manual mode is set.\n",
    /*  8 */  "\tq:\t\tExit to DOS\n",
    /*  9 */  "Connection error!\n",
    /* 10 */  "\nPress <ESC> to back to the menu\n\n",
    /* 11 */  "\nTest device via Hypertext Transfer Protocol:\n\n",
    /* 12 */  "Get information about device",
    /* 13 */  "Get operation mode",
    /* 14 */  "Get all measured data",
    /* 15 */  "Get measured temperature",
    /* 16 */  "Get measured relative humidity",
    /* 17 */  "Get measured relative unwanted gas level",
    /* 18 */  "Get status of green LED",
    /* 19 */  "Get status of yellow LED",
    /* 20 */  "Get status of red LED",
    /* 21 */  "Set operation mode",
    /* 22 */  "Set limit values and get all measured data",
    /* 23 */  "Set status of green LED",
    /* 24 */  "Set status of yellow LED",
    /* 25 */  "Set status of red LED",
    /* 26 */  "Set off all LEDs",
    /* 27 */  "\tGreen",
    /* 28 */  "\tYellow",
    /* 29 */  "\tRed",
    /* 30 */  " LED is switched ",
    /* 31 */  "on.\n",
    /* 32 */  "off.\n",
    /* 33 */  "\t All LEDs are switched off.\n",
    /* 34 */  "\tDevice is automatic operation mode.\n",
    /* 35 */  "\tEnter the minimal humidity: ",
    /* 36 */  "\tEnter the humidifier on humidity: ",
    /* 37 */  "\tEnter the humidifier off humidity: ",
    /* 38 */  "\tEnter the maximal humidity: ",
    /* 39 */  "\tEnter the minimal temperature: ",
    /* 40 */  "\tEnter the heating on temperature: ",
    /* 41 */  "\tEnter the heating off temperature: ",
    /* 42 */  "\tEnter the maximal temperature: ",
    /* 43 */  "\tEnter the maximal gas concentrate: ",
    /* 44 */  "\tDevice is manual operation mode.\n",
    /* 45 */  "\tDevice type:\t\t",
    /* 46 */  "\tSoftware version:\t",
    /* 47 */  "\tSerial number:\t\t",
    /* 48 */  "\tRelative gas level:\t",
    /* 49 */  "\tRelative humidity:\t",
    /* 50 */  "\tTemperature:\t\t"
  };
  return message[index];
}

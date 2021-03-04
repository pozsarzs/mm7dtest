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
    "³ MM7DTest v0.1 * Tester program for MM7D air quality measuring device        ³\n",
    "³ Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>             ³\n",
    "Usage:\n\tmm7dtest.exe IP_address UID\n\n",
    "Bad IP address!\n",
    "IP address: ",
    "\nMain menu:\n\n",
    "\tF1:\tTest device via Hypertext Transfer Protocol\n",
    "\tF2:\tTest device via Modbus protocol\n",
    "\tESC:\tExit to DOS\n\n",
    "Connection error!\n",
    "\tESC:\tback to main menu\n\n",
    "\nTest device via Hypertext Transfer Protocol:\n\n",
    "Get information about device",
    "Get all measured data",
    "Get measured temperature",
    "Get measured relative humidity",
    "Get measured relative unwanted gas level",
    "On/Off green status LED",
    "On/Off yellow status LED",
    "On/Off red status LED",
    "Off all LEDs",
    "Set limit values and get all measured data",
    "\tGreen",
    "\tYellow",
    "\tRed",
    " LED is switched ",
    "on.\n",
    "off.\n",
    "\t All LEDs are switched off.\n",
    "\nTest device via Modbus protocol:\n\n",
    "\tEnter the minimal humidity: ",
    "\tEnter the humidifier on humidity: ",
    "\tEnter the humidifier off humidity: ",
    "\tEnter the maximal humidity: ",
    "\tEnter the minimal temperature: ",
    "\tEnter the heating on temperature: ",
    "\tEnter the heating off temperature: ",
    "\tEnter the maximal temperature: ",
    "\tEnter the maximal gas concentrate: ",
  };
  return message[index];
}

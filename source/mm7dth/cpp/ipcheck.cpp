// +---------------------------------------------------------------------------+
// | MM7DTest v0.1 * Tester program for MM7D air quality measuring device      |
// | Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>           |
// | ipcheck.cpp                                                               |
// | IP address validator                                                      |
// +---------------------------------------------------------------------------+

//   This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License 3.0 version.
//
//   This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// validate number
int validate_number(char *str)
{
  while (*str)
  {
    if (!isdigit(*str)) return 0;
    str++;
  }
  return 1;
}

// validate w.x.y.z format IP address
int validate_ip(char *ip)
{
  int i, num, dots = 0;
  char *ptr;
  if (ip == NULL) return 0;
  ptr = strtok(ip, ".");
  if (ptr == NULL) return 0;
  while (ptr)
  {
    if (!validate_number(ptr)) return 0;
    num = atoi(ptr);
    if (num >= 0 && num <= 255)
    {
      ptr = strtok(NULL, ".");
      if (ptr != NULL) dots++;
    } else return 0;
  }
  if (dots != 3) return 0;
  return 1;
}

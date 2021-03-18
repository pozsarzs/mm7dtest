// +---------------------------------------------------------------------------+
// | MM7DTest v0.1 * Tester program for MM7D air quality measuring device      |
// | Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>           |
// | t_http.cpp                                                                |
// | Tester for HTTP                                                           |
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

// general variables
char      *outBuffer;
bool       greenled     = 0;
bool       yellowled    = 0;
bool       redled       = 0;
bool       autoopmode   = 0;

#define    HTTPGETPROG  "wget -qO "
#define    TEMPFILE     "mm7dtest.tmp"

// write header with menu
void headerwithmenu(int menu)
{
  cls();
  cout << "Ú";  for (int i = 0; i < 77; i++) cout << "Ä"; cout << "¿";
  cout << "\n";
  cout << msg(0) << msg(1);
  cout << "À";  for (int i = 0; i < 77; i++) cout << "Ä"; cout << "Ù"; cout << "\n";
  if (menu == 0)
  {
    cout << msg(11);
    for (int i = 5; i < 20; i++)
    {
       if (i<14) cout <<"\tF" << i-4 << ":\t\t" << msg(i+7) <<"\n";
       if ((i>13) && (i<16)) cout <<"\tShift-F" << i-12 << ":\t" << msg(i+7) <<"\n";
       if (i>15) cout <<"\tShift-F" << i-9 << ":\t" << msg(i+7) <<"\n";
    }
    cout << msg(8);
  } else
  {
    if (menu>17)
      cout << "\n" << msg(menu) << ":\n\n"; else
      cout << "\n" << msg(menu+11) << ":\n\n";
  }
}

// open webpage and save content to temporary file
int openwebpage(char *url, bool readfile)
{
  int rc;
  char *commandline = (char*)malloc(255);
  sprintf(commandline,"%s%s http://%s",HTTPGETPROG,TEMPFILE,url);
  rc = system(commandline);
  free(commandline);
  if ((rc == 0) && (readfile))
  {
    FILE *fp = fopen(TEMPFILE,"rb");
    fseek(fp,0,SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);
    char *string = (char*) malloc(fsize + 1);
    fread(string,1,fsize,fp);
    fclose(fp);
    string[fsize] = 0;
    strcpy(outBuffer,string);
    free(string);
  }
  return rc;
}

// get information about device
void f01(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(1);
  sprintf(url,"%s/version",ip);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << msg(45) << token << "\n";
      if (line == 1) cout << msg(46) << token << "\n";
      if (line == 2) cout << msg(47) << token << "\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(9);
  pause(27,msg(10));
}

// get operation mode
void f02(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(2);
  sprintf(url,"%s/mode?uid=%s",ip,id);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0)
        if (strncmp(token,"1",1) == 0) cout << msg(34);  else  cout << msg(44);
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(0);
  pause(27,msg(10));
}

// get all measured data
void f03(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(3);
  sprintf(url,"%s/get/all?uid=%s",ip,id);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << msg(48) << token << "%\n";
      if (line == 1) cout << msg(49) << token << "%\n";
      if (line == 2) cout << msg(50) << token << " øC\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(9);
  pause(27,msg(10));
}

// get measured temperature
void f04(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(4);
  sprintf(url,"%s/get/temperature?uid=%s",ip,id);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << msg(50) << token << " øC\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(0);
  pause(27,msg(10));
}

// get measured relative humidity
void f05(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(5);
  sprintf(url,"%s/get/humidity?uid=%s",ip,id);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << msg(49) << token << "%\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(0);
  pause(27,msg(10));
}

// get measured relative unwanted gas level
void f06(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(6);
  sprintf(url,"%s/get/unwantedgaslevel?uid=%s",ip,id);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << msg(48) << token << "%\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(0);
  pause(27,msg(10));
}

// get status of green LED
void f07(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(18);
  sprintf(url,"%s/get/greenled?uid=%s",ip,id);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0)
        if (strncmp(token,"1",1) == 0)
          cout << msg(27) << msg(30) << msg(31); else
          cout << msg(27) << msg(30) << msg(32);
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(0);
  pause(27,msg(10));
}

// get status of yellow LED
void f08(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(19);
  sprintf(url,"%s/get/yellowled?uid=%s",ip,id);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0)
        if (strncmp(token,"1",1) == 0)
          cout << msg(28) << msg(30) << msg(31); else
          cout << msg(28) << msg(30) << msg(32);
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(0);
  pause(27,msg(10));
}

// get status of red LED
void f09(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(20);
  sprintf(url,"%s/get/redled?uid=%s",ip,id);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0)
        if (strncmp(token,"1",1) == 0)
          cout << msg(29) << msg(30) << msg(31); else
          cout << msg(29) << msg(30) << msg(32);
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(0);
  pause(27,msg(10));
}

// set operation mode
void sf02(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(21);
  autoopmode = ! autoopmode;
  if (autoopmode) cout << msg(7); else cout << msg(6);
  if (autoopmode)
    sprintf(url,"%s/mode/manual?uid=%s",ip,id); else
    sprintf(url,"%s/mode/auto?uid=%s",ip,id);
  rc = openwebpage(url,0);
  free(url);
  if (rc != 0) cerr << msg(9);
  pause(27,msg(10));
}

// set limit values and get all measured data
void sf03(char *ip, char *id)
{
  int rc;
  int humidity_min, humidifier_on, humidifier_off, humidity_max;
  int temperature_min, heater_on, heater_off, temperature_max;
  int gasconcentrate_max;
  char *url = (char*) malloc(255);
  headerwithmenu(22);
  cout << msg(35);
  cin >> humidity_min;
  cout << msg(36);
  cin >> humidifier_on;
  cout << msg(37);
  cin >> humidifier_off;
  cout << msg(38);
  cin >> humidity_max;
  cout << msg(39);
  cin >> temperature_min;
  cout << msg(40);
  cin >> heater_on;
  cout << msg(41);
  cin >> heater_off;
  cout << msg(42);
  cin >> temperature_max;
  cout << msg(43);
  cin >> gasconcentrate_max;
  delay(500);
  headerwithmenu(22);
  sprintf(url,"%s/operation?uid=%s&h1=%d&h2=%d&h3=%d&h4=%d&t1=%d&t2=%d&t3=%d&t4=%d&g=%d",
              ip, id,
              humidity_min, humidifier_on, humidifier_off, humidity_max,
              temperature_min, heater_on, heater_off, temperature_max,
              gasconcentrate_max);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << msg(48) << token << "%\n";
      if (line == 1) cout << msg(49) << token << "%\n";
      if (line == 2) cout << msg(50) << token << " øC\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(9);
  pause(27,msg(10));
}

// on/off green status LED
void sf07(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(23);
  greenled = ! greenled;
  if (greenled)
    cout << msg(27) << msg(30) << msg(32); else
    cout << msg(27) << msg(30) << msg(31);
  if (greenled)
    sprintf(url,"%s/set/greenled/off?uid=%s",ip,id); else
    sprintf(url,"%s/set/greenled/on?uid=%s",ip,id);
  rc = openwebpage(url,0);
  free(url);
  if (rc != 0) cerr << msg(9);
  pause(27,msg(10));
}

// on/off yellow status LED
void sf08(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(24);
  yellowled = ! yellowled;
  if (yellowled)
    cout << msg(28) << msg(30) << msg(32); else
    cout << msg(28) << msg(30) << msg(31);
  if (yellowled)
    sprintf(url,"%s/set/yellowled/off?uid=%s",ip,id); else
    sprintf(url,"%s/set/yellowled/on?uid=%s",ip,id);
  rc = openwebpage(url,0);
  free(url);
  if (rc != 0) cerr << msg(9);
  pause(27,msg(10));
}

// on/off red status LED
void sf09(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(25);
  redled = ! redled;
  if (redled)
    cout << msg(29) << msg(30) << msg(32); else
    cout << msg(29) << msg(30) << msg(31);
  if (redled)
    sprintf(url,"%s/set/redled/off?uid=%s",ip,id); else
    sprintf(url,"%s/set/redled/on?uid=%s",ip,id);
  rc = openwebpage(url,0);
  free(url);
  if (rc != 0) cerr << msg(9);
  pause(27,msg(10));
}

// off all status LEDs
void sf10(char *ip, char *id)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(26);
  cout << msg(33);
  sprintf(url,"%s/set/all/off?uid=%s",ip,id);
  rc = openwebpage(url,0);
  free(url);
  if (rc != 0) cerr << msg(9);
  pause(27,msg(10));
}

// main function
void httptest(char *ip, char *id)
{
  // menu
  headerwithmenu(0);
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
          case 59:  f01(ip,id); headerwithmenu(0); break;
          case 60:  f02(ip,id); headerwithmenu(0); break;
          case 61:  f03(ip,id); headerwithmenu(0); break;
          case 62:  f04(ip,id); headerwithmenu(0); break;
          case 63:  f05(ip,id); headerwithmenu(0); break;
          case 64:  f06(ip,id); headerwithmenu(0); break;
          case 65:  f07(ip,id); headerwithmenu(0); break;
          case 66:  f08(ip,id); headerwithmenu(0); break;
          case 67:  f09(ip,id); headerwithmenu(0); break;
          case 85: sf02(ip,id); headerwithmenu(0); break;
          case 86: sf03(ip,id); headerwithmenu(0); break;
          case 90: sf07(ip,id); headerwithmenu(0); break;
          case 91: sf08(ip,id); headerwithmenu(0); break;
          case 92: sf09(ip,id); headerwithmenu(0); break;
          case 93: sf10(ip,id); headerwithmenu(0); break;
        }
      }
      if (ch == 27) repeat = false;
    }
  }
}

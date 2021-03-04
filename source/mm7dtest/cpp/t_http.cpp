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

#define    HTTPGETPROG  "htget -quiet -o"
#define    TEMPFILE     "mm7dtest.tmp"

// write header with menu
void hheaderwithmenu(int menu)
{
  cls();
  cout << "Ú";  for (int i = 0; i < 77; i++) cout << "Ä"; cout << "¿";
  cout << "\n";
  cout << msg(0) << msg(1);
  cout << "À";  for (int i = 0; i < 77; i++) cout << "Ä"; cout << "Ù"; cout << "\n";
  if (menu == 0)
  {
    cout << msg(11);
    for (int i = 5; i < 15; i++)
       cout <<"\tF" << i-4 << ":\t" << msg(i+7) <<"\n";
    cout << msg(10);
  } else
    if (menu == 11) cout << msg(30); else cout << "\n" << msg(menu+11) << ":\n\n";
}

// open webpage and save content to temporary file
int openwebpage(char *url)
{
  int rc;
  char commandline[255];
  sprintf(commandline,"%s %s http://%s",HTTPGETPROG,TEMPFILE,url);
  rc = system(commandline);
  if (rc == 0)
  {
    char *string;
    FILE *fp = fopen(TEMPFILE,"rb");
    fseek(fp,0,SEEK_END);
    long fsize = ftell(fp);
    rewind(fp);
    string = (char*) malloc(fsize + 1);
    fread(string,1,fsize,fp);
    fclose(fp);
    string[fsize] = 0;
    strcpy(outBuffer,string);
    free(string);
  }
  return rc;
}

// get information about device
void hf1(char *ip, char *id)
{
  int rc;
  char url[127];
  hheaderwithmenu(1);
  sprintf(url,"%s/version",ip);
  rc = openwebpage(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << "\tDevice type:\t\t" << token << "\n";
      if (line == 1) cout << "\tSoftware version:\t" << token << "\n";
      if (line == 2) cout << "\tSerial number:\t\t" << token << "\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(9);
  pause(27);
}

// get all measured data
void hf2(char *ip, char *id)
{
  int rc;
  char url[127];
  hheaderwithmenu(2);
  sprintf(url,"%s/get/all?uid=%s",ip,id);
  rc = openwebpage(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << "\tRelative gas level:\t" << token << "%\n";
      if (line == 1) cout << "\tRelative humidity:\t" << token << "%\n";
      if (line == 2) cout << "\tTemperature:\t\t" << token << " øC\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(9);
  pause(27);
}

// get measured temperature
void hf3(char *ip, char *id)
{
  int rc;
  char url[127];
  hheaderwithmenu(3);
  sprintf(url,"%s/get/temperature?uid=%s",ip,id);
  rc = openwebpage(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << "\tTemperature:\t\t" << token << " øC\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(0);
  pause(27);
}

// get measured relative humidity
void hf4(char *ip, char *id)
{
  int rc;
  char url[127];
  hheaderwithmenu(4);
  sprintf(url,"%s/get/humidity?uid=%s",ip,id);
  rc = openwebpage(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << "\tRelative humidity:\t" << token << "%\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(0);
  pause(27);
}

// get measured relative unwanted gas level
void hf5(char *ip, char *id)
{
  int rc;
  char url[127];
  hheaderwithmenu(5);
  sprintf(url,"%s/get/unwantedgaslevel?uid=%s",ip,id);
  rc = openwebpage(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << "\tRelative gas level:\t" << token << "%\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(0);
  pause(27);
}

// on/off green status LED
void hf6(char *ip, char *id)
{
  int rc;
  char url[127];
  hheaderwithmenu(6);
  greenled = ! greenled;
  if (greenled)
    cout << msg(22) << msg(25) << msg(27); else
    cout << msg(22) << msg(25) << msg(26);
  if (greenled)
    sprintf(url,"%s/set/greenled/off?uid=%s",ip,id); else
    sprintf(url,"%s/set/greenled/on?uid=%s",ip,id);
  rc = openwebpage(url);
  if (rc != 0) cerr << msg(9);
  delay(1000);
}

// on/off yellow status LED
void hf7(char *ip, char *id)
{
  int rc;
  char url[127];
  hheaderwithmenu(7);
  yellowled = ! yellowled;
  if (yellowled)
    cout << msg(23) << msg(25) << msg(27); else
    cout << msg(23) << msg(25) << msg(26);
  if (yellowled)
    sprintf(url,"%s/set/yellowled/off?uid=%s",ip,id); else
    sprintf(url,"%s/set/yellowled/on?uid=%s",ip,id);
  rc = openwebpage(url);
  if (rc != 0) cerr << msg(9);
  delay(1000);
}

// on/off red status LED
void hf8(char *ip, char *id)
{
  int rc;
  char url[127];
  hheaderwithmenu(8);
  redled = ! redled;
  if (redled)
    cout << msg(24) << msg(25) << msg(27); else
    cout << msg(24) << msg(25) << msg(26);
  if (redled)
    sprintf(url,"%s/set/redled/off?uid=%s",ip,id); else
    sprintf(url,"%s/set/redled/on?uid=%s",ip,id);
  rc = openwebpage(url);
  if (rc != 0) cerr << msg(9);
  delay(1000);
}

// off all status LEDs
void hf9(char *ip, char *id)
{
  int rc;
  char url[127];
  hheaderwithmenu(9);
  cout << msg(28);
  sprintf(url,"%s/set/all/off?uid=%s",ip,id);
  rc = openwebpage(url);
  if (rc != 0) cerr << msg(9);
  delay(1000);
}

// set limit values and get all measured data
void hf10(char *ip, char *id)
{
  int rc;
  int humidity_min, humidifier_on, humidifier_off, humidity_max;
  int temperature_min, heater_on, heater_off, temperature_max;
  int gasconcentrate_max;
  char url[127];
  hheaderwithmenu(10);
  cout << msg(30);
  cin >> humidity_min;
  cout << msg(31);
  cin >> humidifier_on;
  cout << msg(32);
  cin >> humidifier_off;
  cout << msg(33);
  cin >> humidity_max;
  cout << msg(34);
  cin >> temperature_min;
  cout << msg(35);
  cin >> heater_on;
  cout << msg(36);
  cin >> heater_off;
  cout << msg(37);
  cin >> temperature_max;
  cout << msg(38);
  cin >> gasconcentrate_max;
  delay(1000);
  hheaderwithmenu(10);
  sprintf(url,"%s/operation?uid=%s&h1=%d&h2=%d&h3=%d&h4=%d&t1=%d&t2=%d&t3=%d&t4=%d&g=%d",
              ip, id,
              humidity_min, humidifier_on, humidifier_off, humidity_max,
              temperature_min, heater_on, heater_off, temperature_max,
              gasconcentrate_max);
  rc = openwebpage(url);
  if (rc == 0)
  {
    char *input;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) cout << "\tRelative gas level:\t" << token << "%\n";
      if (line == 1) cout << "\tRelative humidity:\t" << token << "%\n";
      if (line == 2) cout << "\tTemperature:\t\t" << token << " øC\n";
      token = strtok(NULL,"\n");
      line++;
    }
  } else cerr << msg(9);
  pause(27);
}

// main function
void httptest(char *ip, char *id)
{
  // menu
  hheaderwithmenu(0);
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
            hf1(ip,id);
            hheaderwithmenu(0);
            break;
          case 60:
            hf2(ip,id);
            hheaderwithmenu(0);
            break;
          case 61:
            hf3(ip,id);
            hheaderwithmenu(0);
            break;
          case 62:
            hf4(ip,id);
            hheaderwithmenu(0);
            break;
          case 63:
            hf5(ip,id);
            hheaderwithmenu(0);
            break;
          case 64:
            hf6(ip,id);
            hheaderwithmenu(0);
            break;
          case 65:
            hf7(ip,id);
            hheaderwithmenu(0);
            break;
          case 66:
            hf8(ip,id);
            hheaderwithmenu(0);
            break;
          case 67:
            hf9(ip,id);
            hheaderwithmenu(0);
            break;
          case 68:
            hf10(ip,id);
            hheaderwithmenu(0);
            break;
        }
      }
      if (ch == 27) repeat = false;
    }
  }
}

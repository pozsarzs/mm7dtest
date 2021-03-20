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
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include "messages.h"
#include "utils.h"

using namespace std;

// general variables
char      *outBuffer    = (char*) malloc(255);
char      *ip           = (char*) malloc(15);
char      *uid          = (char*) malloc(255);
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
#ifdef __DOS__
  printf("Ú"); for (int i = 0; i < 77; i++) printf("Ä"); printf("¿\n");
  printf("³ %s³\n",msg(0));
  printf("³ %s³\n",msg(1));
  printf("À"); for (int i = 0; i < 77; i++) printf("Ä"); printf("Ù\n");
#else
  printf("+"); for (int i = 0; i < 77; i++) printf("-"); printf("+\n");
  printf("| %s|\n",msg(0));
  printf("| %s|\n",msg(1));
  printf("+"); for (int i = 0; i < 77; i++) printf("-"); printf("+\n");
#endif
  if (menu == 0)
  {
    printf(msg(11));
    for (int i = 5; i < 20; i++) printf("\t%x:\t\t%s\n",i-4,msg(i+7));
    printf(msg(8));
  } else
  {
    if (menu>17)
      printf("\n%s:\n\n",msg(menu)); else
      printf("\n%s:\n\n",msg(menu+11));
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
void f01(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(1);
  sprintf(url,"%s/version",ip);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input = (char*) malloc(255);
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) printf("%s%s\n",msg(45),token);
      if (line == 1) printf("%s%s\n",msg(46),token);
      if (line == 2) printf("%s%s\n",msg(47),token);
      token = strtok(NULL,"\n");
      line++;
    }
    free(input);
  } else printf(msg(9));
  pause(27,msg(10));
}

// get operation mode
void f02(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(2);
  sprintf(url,"%s/mode?uid=%s",ip,uid);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input = (char*) malloc(255);
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0)
        if (strncmp(token,"1",1) == 0) printf(msg(34)); else printf(msg(44));
      token = strtok(NULL,"\n");
      line++;
    }
    free(input);
  } else printf(msg(9));
  pause(27,msg(10));
}

// get all measured data
void f03(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(3);
  sprintf(url,"%s/get/all?uid=%s",ip,uid);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input = (char*) malloc(255);
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) printf("%s%s %% \n",msg(48),token);
      if (line == 1) printf("%s%s %% \n",msg(49),token);
#ifdef __DOS__
      if (line == 2) printf("%s%s øC\n",msg(50),token);
#else
      if (line == 2) printf("%s%s Â°C\n",msg(50),token);
#endif
      token = strtok(NULL,"\n");
      line++;
    }
    free(input);
  } else printf(msg(9));
  pause(27,msg(10));
}

// get measured temperature
void f04(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(4);
  sprintf(url,"%s/get/temperature?uid=%s",ip,uid);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input = (char*) malloc(255);
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
#ifdef __DOS__
      if (line == 0) printf("%s%s øC\n",msg(50),token);
#else
      if (line == 0) printf("%s%s Â°C\n",msg(50),token);
#endif
      token = strtok(NULL,"\n");
      line++;
    }
    free(input);
  } else printf(msg(9));
  pause(27,msg(10));
}


// get measured relative humidity
void f05(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(5);
  sprintf(url,"%s/get/humidity?uid=%s",ip,uid);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input = (char*) malloc(255);
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) printf("%s%s %% \n",msg(49),token);
      token = strtok(NULL,"\n");
      line++;
    }
    free(input);
  } else printf(msg(9));
  pause(27,msg(10));
}

// get measured relative unwanted gas level
void f06(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(6);
  sprintf(url,"%s/get/unwantedgaslevel?uid=%s",ip,uid);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input = (char*) malloc(255);
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) printf("%s%s %% \n",msg(48),token);
      token = strtok(NULL,"\n");
      line++;
    }
    free(input);
  } else printf(msg(9));
  pause(27,msg(10));
}

// get status of green LED
void f07(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(18);
  sprintf(url,"%s/get/greenled?uid=%s",ip,uid);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input = (char*) malloc(255);
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0)
        if (strncmp(token,"1",1) == 0)
          printf("%s%s%s",msg(27),msg(30),msg(31)); else
          printf("%s%s%s",msg(27),msg(30),msg(32));
      token = strtok(NULL,"\n");
      line++;
    }
    free(input);
  } else printf(msg(9));
  pause(27,msg(10));
}

// get status of yellow LED
void f08(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(19);
  sprintf(url,"%s/get/yellowled?uid=%s",ip,uid);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input = (char*) malloc(255);
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0)
        if (strncmp(token,"1",1) == 0)
          printf("%s%s%s",msg(28),msg(30),msg(31)); else
          printf("%s%s%s",msg(28),msg(30),msg(32));
      token = strtok(NULL,"\n");
      line++;
    }
    free(input);
  } else printf(msg(9));
  pause(27,msg(10));
}

// get status of red LED
void f09(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(20);
  sprintf(url,"%s/get/redled?uid=%s",ip,uid);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input = (char*) malloc(255);
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0)
        if (strncmp(token,"1",1) == 0)
          printf("%s%s%s",msg(29),msg(30),msg(31)); else
          printf("%s%s%s",msg(29),msg(30),msg(32));
      token = strtok(NULL,"\n");
      line++;
    }
    free(input);
  } else printf(msg(9));
  pause(27,msg(10));
}

// set operation mode
void f10(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(21);
  autoopmode = ! autoopmode;
  if (autoopmode) printf(msg(7)); else printf(msg(6));
  if (autoopmode)
    sprintf(url,"%s/mode/manual?uid=%s",ip,uid); else
    sprintf(url,"%s/mode/auto?uid=%s",ip,uid);
  rc = openwebpage(url,0);
  free(url);
  if (rc != 0) printf(msg(9));
  pause(27,msg(10));
}

// set limit values and get all measured data
void f11(void)
{
  int rc;
  int humidity_min, humidifier_on, humidifier_off, humidity_max;
  int temperature_min, heater_on, heater_off, temperature_max;
  int gasconcentrate_max;
  char *url = (char*) malloc(255);
  headerwithmenu(22);
  printf(msg(35));
  scanf("%d",&humidity_min);
  printf(msg(36));
  scanf("%d",&humidifier_on);
  printf(msg(37));
  scanf("%d",&humidifier_off);
  printf(msg(38));
  scanf("%d",&humidity_max);
  printf(msg(39));
  scanf("%d",&temperature_min);
  printf(msg(40));
  scanf("%d",&heater_on);
  printf(msg(41));
  scanf("%d",&heater_off);
  printf(msg(42));
  scanf("%d",&temperature_max);
  printf(msg(43));
  scanf("%d",&gasconcentrate_max);
  headerwithmenu(22);
  sprintf(url,"%s/operation?uid=%s&h1=%d&h2=%d&h3=%d&h4=%d&t1=%d&t2=%d&t3=%d&t4=%d&g=%d",
              ip, uid,
              humidity_min, humidifier_on, humidifier_off, humidity_max,
              temperature_min, heater_on, heater_off, temperature_max,
              gasconcentrate_max);
  rc = openwebpage(url,1);
  free(url);
  if (rc == 0)
  {
    char *input = (char*) malloc(255);;
    strcpy(input,outBuffer);
    char *token = strtok(input,"\n");
    int line = 0;
    while (token != NULL)
    {
      if (line == 0) printf("%s%s %% \n",msg(48),token);
      if (line == 1) printf("%s%s %% \n",msg(49),token);
#ifdef __DOS__
      if (line == 2) printf("%s%s øC\n",msg(50),token);
#else
      if (line == 2) printf("%s%s Â°C\n",msg(50),token);
#endif
      token = strtok(NULL,"\n");
      line++;
    }
    free(input);
  } else printf(msg(9));
  pause(27,msg(10));
}

// on/off green status LED
void f12(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(23);
  greenled = ! greenled;
  if (greenled)
    printf("%s%s%s",msg(27),msg(30),msg(32)); else
    printf("%s%s%s",msg(27),msg(30),msg(31));
  if (greenled)
    sprintf(url,"%s/set/greenled/off?uid=%s",ip,uid); else
    sprintf(url,"%s/set/greenled/on?uid=%s",ip,uid);
  rc = openwebpage(url,0);
  free(url);
  if (rc != 0) printf(msg(9));
  pause(27,msg(10));
}

// on/off yellow status LED
void f13(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(24);
  yellowled = ! yellowled;
  if (yellowled)
    printf("%s%s%s",msg(28),msg(30),msg(32)); else
    printf("%s%s%s",msg(28),msg(30),msg(31));
  if (yellowled)
    sprintf(url,"%s/set/yellowled/off?uid=%s",ip,uid); else
    sprintf(url,"%s/set/yellowled/on?uid=%s",ip,uid);
  rc = openwebpage(url,0);
  free(url);
  if (rc != 0) printf(msg(9));
  pause(27,msg(10));
}

// on/off red status LED
void f14(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(25);
  redled = ! redled;
  if (redled)
    printf("%s%s%s",msg(29),msg(30),msg(32)); else
    printf("%s%s%s",msg(29),msg(30),msg(31));
  if (redled)
    sprintf(url,"%s/set/redled/off?uid=%s",ip,uid); else
    sprintf(url,"%s/set/redled/on?uid=%s",ip,uid);
  rc = openwebpage(url,0);
  free(url);
  if (rc != 0) printf(msg(9));
  pause(27,msg(10));
}

// off all status LEDs
void f15(void)
{
  int rc;
  char *url = (char*) malloc(255);
  headerwithmenu(26);
  printf(msg(33));
  sprintf(url,"%s/set/all/off?uid=%s",ip,uid);
  rc = openwebpage(url,0);
  free(url);
  if (rc != 0) printf(msg(9));
  pause(27,msg(10));
}

// main function
void httptest(char *iip, char *iuid)
{
  strcpy(ip,iip);
  strcpy(uid,iuid);
  // menu
  headerwithmenu(0);
  bool repeat = true;
  char ch;
  while (repeat)
  {
    if (kbhit())
    {
      ch = getch();
      switch (ch)
      {
        case '1': f01(); headerwithmenu(0); break;
        case '2': f02(); headerwithmenu(0); break;
        case '3': f03(); headerwithmenu(0); break;
        case '4': f04(); headerwithmenu(0); break;
        case '5': f05(); headerwithmenu(0); break;
        case '6': f06(); headerwithmenu(0); break;
        case '7': f07(); headerwithmenu(0); break;
        case '8': f08(); headerwithmenu(0); break;
        case '9': f09(); headerwithmenu(0); break;
        case 'a': f10(); headerwithmenu(0); break;
        case 'b': f11(); headerwithmenu(0); break;
        case 'c': f12(); headerwithmenu(0); break;
        case 'd': f13(); headerwithmenu(0); break;
        case 'e': f14(); headerwithmenu(0); break;
        case 'f': f15(); headerwithmenu(0); break;
      }
      if (ch == 'q') repeat = false;
    }
  }
}

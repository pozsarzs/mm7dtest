@echo off
rem MM7DTest v0.1 * Tester program for MM7D air quality measuring device
rem Copyright (C) 2021 Pozsar Zsolt pozsar.zsolt@szerafingomba.hu
rem build.bat
rem Builder batch file for DOS
rem 
rem   This program is free software: you can redistribute it and/or modify it
rem under the terms of the GNU General Public License 3.0 version.
rem 
rem   This program is distributed in the hope that it will be useful, but WITHOUT
rem ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
rem FOR A PARTICULAR PURPOSE.

wmake -e -f Makefile.dos %1

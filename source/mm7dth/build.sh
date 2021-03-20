#!/bin/bash
# +----------------------------------------------------------------------------+
# | MM7DTest v0.1 * Tester program for MM7D air quality measuring device       |
# | Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>            |
# | build.sh                                                                   |
# | Builder script for linux                                                   |
# +----------------------------------------------------------------------------+

wmake -e -f Makefile.linux $1

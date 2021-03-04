# +----------------------------------------------------------------------------+
# | MM7DTest v0.1 * Tester program for MM7D air quality measuring device       |
# | Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>            |
# | makefile                                                                   |
# | Makefile for DOS                                                           |
# +----------------------------------------------------------------------------+

compile_options = -0 -ml -i=h -i=cpp
objs =  mbget.obj

all: mbget.exe

clean : .symbolic
  @del mbget.exe
  @del *.obj
  @del *.lnk
  @del *.map

install : .symbolic
  @copy mbget.exe ..\..

.cpp : cpp

.cpp.obj :
  wpp $[* $(compile_options)

mm7dtest.exe: $(objs)
  wlink system dos option map option eliminate option stack=4096 name $@ file *.obj

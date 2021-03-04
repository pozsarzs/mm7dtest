# +----------------------------------------------------------------------------+
# | MM7DTest v0.1 * Tester program for MM7D air quality measuring device       |
# | Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>            |
# | makefile                                                                   |
# | Makefile for DOS                                                           |
# +----------------------------------------------------------------------------+

compile_options = -0 -ml -i=h -i=cpp
objs = ipcheck.obj messages.obj utils.obj t_http.obj t_modbus.obj mm7dtest.obj

all: mm7dtest.exe

clean : .symbolic
  @del mm7dtest.exe
  @del *.obj
  @del *.lnk
  @del *.map

install : .symbolic
  @copy mm7dtest.exe ..\..

.cpp : cpp

.cpp.obj :
  wpp $[* $(compile_options)

mm7dtest.exe: $(objs)
  wlink system dos option map option eliminate option stack=4096 name $@ file *.obj

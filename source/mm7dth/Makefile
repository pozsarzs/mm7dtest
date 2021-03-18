# +----------------------------------------------------------------------------+
# | MM7DTest v0.1 * Tester program for MM7D air quality measuring device       |
# | Copyright (C) 2021 Pozsar Zsolt <pozsar.zsolt@szerafingomba.hu>            |
# | makefile                                                                   |
# | Makefile for DOS                                                           |
# +----------------------------------------------------------------------------+

processor=-0
memory_model=-ml
dircpp=cpp
dirh=h
compile_options = $(processor) $(memory_model) -bc -d0 -i=$(dirh) -i=$(dircpp)
objs = ipcheck.obj messages.obj utils.obj t_http.obj mm7dth.obj

all: mm7dth.exe

clean : .symbolic
  @del mm7dth.exe
  @del *.obj
  @del *.map

install : .symbolic
  @copy mm7dth.exe ..\..

.cpp : $(dircpp)

.cpp.obj :
  wpp $[* $(compile_options)

mm7dth.exe: $(objs)
  wlink system dos option eliminate option map option stack=4096 name $@ file *.obj

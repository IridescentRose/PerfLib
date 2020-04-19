TARGET = cube
OBJS = cube.o logo.o callbacks.o vram.o

INCDIR = ../../include
CFLAGS = -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR = ../../lib
LDFLAGS =
LIBS= -lperf -lpsprtc -lpspsdk -lpspgum -lpspgu -lm

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = PerfLib Cube Sample

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

logo.o: logo.raw
	bin2o -i logo.raw logo.o logo

CXX ?= g++
LIBS = -g
CFLAGS = -Wall -O2 -fPIC -DUSERSPACE -g -std=c++11 -I. -I./dispdrivers -I./userspace-platform
OPTIONS = 

SRCS = \
       canvas.cpp \
       codepages.cpp \
       collisiondetector.cpp \
       devdrivers/kbdlayouts.cpp \
       devdrivers/keyboard.cpp \
       devdrivers/soundgen.cpp \
       dispdrivers/vga16controller.cpp \
       dispdrivers/vga2controller.cpp \
       dispdrivers/vga4controller.cpp \
       dispdrivers/vga8controller.cpp \
       dispdrivers/vgabasecontroller.cpp \
       dispdrivers/vgacontroller.cpp \
       dispdrivers/vgapalettedcontroller.cpp \
       displaycontroller.cpp \
       fabfonts.cpp \
       fabutils.cpp \
       terminal.cpp \
       terminfo.cpp \
       userspace-platform/esp32time.cpp \
       userspace-platform/fake_misc.cpp \
       userspace-platform/Stream.cpp \
       userspace-platform/HardwareSerial.cpp \
       userspace-platform/ps2controller.cpp \

OBJS = $(SRCS:.cpp=.o)

.cpp.o:
	$(CXX) $(CFLAGS) $(OPTIONS) -c $< -o $@

vdp-gl.a: $(OBJS)
	ar -rcs vdp-gl.a $(OBJS) 

clean:
	-rm $(OBJS)
	-rm vdp-gl.a

depends: $(SRCS)
	$(CXX) -MM $(CFLAGS) $(SRCS) > Makefile.dep

ifneq (,$(wildcard Makefile.dep))
include Makefile.dep
endif

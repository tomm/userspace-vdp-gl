CXX ?= g++
LIBS = -g
CFLAGS = $(EXTRA_FLAGS) -Wall -O2 -fPIC -fno-exceptions -DUSERSPACE -g -std=c++11 -I. -I./dispdrivers -I./comdrivers -I./userspace-platform
OPTIONS = 

SRCS = \
       canvas.cpp \
       codepages.cpp \
       collisiondetector.cpp \
       comdrivers/ps2device.cpp \
       comdrivers/ps2controller.cpp \
       devdrivers/kbdlayouts.cpp \
       devdrivers/keyboard.cpp \
       devdrivers/mouse.cpp \
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
       userspace-platform/heap_allocator.cpp \
       userspace-platform/Stream.cpp \
       userspace-platform/HardwareSerial.cpp \

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

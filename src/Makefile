CXX ?= g++
AR ?= ar
LIBS = -g
CFLAGS = $(EXTRA_FLAGS) -Wall -O2 -fPIC -DUSERSPACE -DWIFI_TASK_CORE_ID=0 -g -std=c++11 -I. -I./dispdrivers -I./comdrivers -I./userspace-platform -I./userspace-platform/matrix
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
       dispdrivers/vgadirectcontroller.cpp \
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
       userspace-platform/matrix/mat.cpp \

OBJS = $(SRCS:.cpp=$(SUFFIX).o)

%$(SUFFIX).o: %.cpp
	$(CXX) $(CFLAGS) $(OPTIONS) -c $< -o $@

.cpp.o:
	$(CXX) $(CFLAGS) $(OPTIONS) -c $< -o $@

vdp-gl$(SUFFIX).a: $(OBJS)
	$(AR) -rcs vdp-gl$(SUFFIX).a $(OBJS) 

clean:
	-rm $(OBJS)
	-rm vdp-gl*.a

depends: $(SRCS)
	$(CXX) -MM $(CFLAGS) $(SRCS) > Makefile.dep

ifneq (,$(wildcard Makefile.dep))
include Makefile.dep
endif

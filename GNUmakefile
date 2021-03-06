# This file was automatically generated by bakefile.
#
# Any manual changes will be lost if it is regenerated,
# modify the source .bkl file instead if possible.

# You may define standard make variables such as CFLAGS or
# CXXFLAGS to affect the build. For example, you could use:
#
#      make CXXFLAGS=-g
#
# to build with debug information. The full list of variables
# that can be used by this makefile is:
# AR, CC, CFLAGS, CPPFLAGS, CXX, CXXFLAGS, LD, LDFLAGS, MAKE, RANLIB.

# You may also specify config=Debug|Release
# or their corresponding lower case variants on make command line to select
# the corresponding default flags values.
ifeq ($(config),debug)
override config := Debug
endif
ifeq ($(config),release)
override config := Release
endif
ifeq ($(config),Debug)
CPPFLAGS ?= -DDEBUG
CFLAGS ?= -g -O0
CXXFLAGS ?= -g -O0
LDFLAGS ?= -g
else ifeq ($(config),Release)
CPPFLAGS ?= -DNDEBUG
CFLAGS ?= -O2
CXXFLAGS ?= -O2
else ifneq (,$(config))
$(warning Unknown configuration "$(config)")
endif

# Use "make RANLIB=''" for platforms without ranlib.
RANLIB ?= ranlib

CC := cc
CXX := c++

# The directory for the build files, may be overridden on make command line.
builddir = .

all: $(builddir)/libgc.a $(builddir)/libthread.a $(builddir)/hsc $(builddir)/hs

$(builddir)/libgc.a: $(builddir)/gc_gc.o
	$(AR) rcu $@ $(builddir)/gc_gc.o
	$(RANLIB) $@

$(builddir)/gc_gc.o: gc.c
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) -MD -MP -fPIC -DPIC -pthread -Iinclude gc.c

$(builddir)/libthread.a: $(builddir)/thread_thread.o
	$(AR) rcu $@ $(builddir)/thread_thread.o
	$(RANLIB) $@

$(builddir)/thread_thread.o: src/thread.c
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) -MD -MP -fPIC -DPIC -pthread -Iinclude src/thread.c

$(builddir)/hsc: $(builddir)/hsc_compiler.o $(builddir)/libgc.a $(builddir)/libthread.a
	$(CXX) -o $@ $(LDFLAGS) $(builddir)/hsc_compiler.o $(builddir)/libgc.a $(builddir)/libthread.a -pthread

$(builddir)/hsc_compiler.o: src/compiler.c
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) -MD -MP -pthread -Iinclude src/compiler.c

$(builddir)/hs: $(builddir)/hs_interpreter.o $(builddir)/libgc.a $(builddir)/libthread.a
	$(CXX) -o $@ $(LDFLAGS) $(builddir)/hs_interpreter.o $(builddir)/libgc.a $(builddir)/libthread.a -pthread

$(builddir)/hs_interpreter.o: src/interpreter.c
	$(CC) -c -o $@ $(CPPFLAGS) $(CFLAGS) -MD -MP -pthread -Iinclude src/interpreter.c

clean:
	rm -f *.o
	rm -f *.d
	rm -f $(builddir)/libgc.a
	rm -f $(builddir)/libthread.a
	rm -f $(builddir)/hsc
	rm -f $(builddir)/hs

.PHONY: all clean

# Dependencies tracking:
-include *.d

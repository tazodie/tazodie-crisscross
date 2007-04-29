include ../common.mk

OBJDIR = obj/linux
OUTDIR = .
OUTNAME = crisscross-test
OUTBIN = $(OUTNAME)

SOURCES = \
testutils.cpp \
stopwatch.cpp \
compare.cpp \
llist.cpp \
rbtree.cpp \
pass.cpp \
fail.cpp \
dstack.cpp \
darray.cpp \
sort.cpp \
splay.cpp \
main.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

ifneq ($(CC_BUILDSTATIC),yes)
LINK += -rdynamic
else
LINK += -L../source
endif
INCLUDES += -I. -I../source
CXXFLAGS += $(INCLUDES)

ifeq ($(GCC_MAJOR),4)
PCH = header.h
GCH = $(PCH).gch
endif

all: .depend $(OUTDIR)/$(OUTBIN)

precomp: $(GCH)

memcheck: $(OUTDIR)/$(OUTBIN)
	LD_LIBRARY_PATH="$(OUTDIR)" valgrind --leak-check=full --db-command='gdb --nw %f %p' --db-attach=yes -v $(OUTDIR)/$(OUTBIN)

clean:
	-rm -rf obj
	-rm -f .depend
	-rm -rf .libs
	-rm -f $(OUTDIR)/$(OUTBIN)
	-rm -f $(OUTDIR)/$(OUTBIN).map
	-rm -f $(PCH)
	-rm -f $(LIBNAME)
	-rm -f $(LIBNAME).$(VERSION_MAJOR)
	-rm -f $(LIBNAME).$(VERSION)

	
$(OUTDIR)/$(OUTBIN): $(OBJECTS)
ifneq ($(CC_BUILDSTATIC),yes)
	$(LINK) $+ -lpthread -lstdc++ -L../source -lCrissCross -o $(OUTDIR)/$(OUTBIN)
	ln -sf ../source/$(LIBNAME).$(VERSION) $(LIBNAME)
	ln -sf ../source/$(LIBNAME).$(VERSION) $(LIBNAME).$(VERSION_MAJOR)
	ln -sf ../source/$(LIBNAME).$(VERSION) $(LIBNAME).$(VERSION)
else
	ln -sf ../source/$(LIBNAME) $(LIBNAME)
	$(LINK) $+ -lpthread -lstdc++ libcrisscross-$(VERSION).a -o $(OUTDIR)/$(OUTBIN)
endif
ifneq ($(GCC_ISEMULATED),yes)
	$(NM) $(OUTDIR)/$(OUTBIN) > $(OUTDIR)/$(OUTBIN).map
endif   
	$(STRIP) $(OUTDIR)/$(OUTBIN)

$(GCH): $(PCH)
	$(CXX) $(CXXFLAGS) -c $(PCH) -o $(GCH)

$(OBJDIR)/%.o: %.cpp
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	$(CC) $(CXXFLAGS) -c $< -o $@

.depend:
ifeq ($(GCC_ISEMULATED),yes)
	../contrib/fastdep-0.15/fastdep $(INCLUDES) --remakedeptarget=.depend $(SOURCES) > .depend
endif

ifneq ($(MAKECMDGOALS),clean)	
-include .depend
endif


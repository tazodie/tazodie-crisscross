include ../common.mk

OBJDIR = obj/linux
OUTDIR = .
OUTNAME = crisscross-test
OUTBIN = $(OUTNAME)

SOURCES = \
testutils.cpp \
stopwatch.cpp \
datatypes.cpp \
compare.cpp \
llist.cpp \
hashtable.cpp \
avltree.cpp \
splaytree.cpp \
rbtree.cpp \
dstack.cpp \
darray.cpp \
bubblesort.cpp \
combsort.cpp \
heapsort.cpp \
insertionsort.cpp \
quicksort.cpp \
shellsort.cpp \
main.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

ifneq ($(CC_BUILDSTATIC),yes)
LDFLAGS += -rdynamic
endif

INCLUDES += -I. -I../source
CXXFLAGS += $(INCLUDES)

ifeq ($(GCC_MAJOR),4)
PCH = header.h
GCH = $(PCH).gch
endif

all: $(OUTDIR)/$(OUTBIN)

precomp: $(GCH)

test: $(OUTDIR)/$(OUTBIN)
ifeq ($(GCC_NDS),)
	LD_LIBRARY_PATH="$(OUTDIR)" $(OUTDIR)/$(OUTBIN)
endif

memcheck: $(OUTDIR)/$(OUTBIN)
ifeq ($(GCC_NDS),)
	LD_LIBRARY_PATH="$(OUTDIR)" valgrind --leak-check=full --db-command='gdb --nw %f %p' --db-attach=yes -v $(OUTDIR)/$(OUTBIN)
endif

clean:
	-rm -rf obj
	-rm -f .depend
	-rm -rf .libs
	-rm -f $(OUTDIR)/$(OUTBIN)
ifneq ($(GCC_NDS),)
	-rm -f $(OUTDIR)/$(OUTBIN).nds
	-rm -f $(OUTDIR)/$(OUTBIN).arm9
endif
	-rm -f $(OUTDIR)/$(OUTBIN).map
	-rm -f $(GCH)
ifneq ($(CC_BUILDSTATIC),yes)
	-rm -f $(LIBNAME)
	-rm -f $(LIBNAME).$(VERSION_MAJOR)
	-rm -f $(LIBNAME).$(VERSION)
endif

	
$(OUTDIR)/$(OUTBIN): $(OBJECTS)
ifneq ($(CC_BUILDSTATIC),yes)
	$(LINK) $+ $(LDFLAGS) -o $(OUTDIR)/$(OUTBIN)
	ln -sf ../source/$(LIBNAME).$(VERSION) $(LIBNAME)
	ln -sf ../source/$(LIBNAME).$(VERSION) $(LIBNAME).$(VERSION_MAJOR)
	ln -sf ../source/$(LIBNAME).$(VERSION) $(LIBNAME).$(VERSION)
	ln -sf ../source/$(LIBNAME) $(LIBNAME)
else
	$(LINK) $+ $(LDFLAGS) -o $(OUTDIR)/$(OUTBIN)
endif
ifneq ($(GCC_NDS),)
	arm-eabi-objcopy -O binary $(OUTDIR)/$(OUTBIN) $(OUTDIR)/$(OUTBIN).arm9
	ndstool -c $(OUTDIR)/$(OUTBIN).nds -9 $(OUTDIR)/$(OUTBIN).arm9
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

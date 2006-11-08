include ../common.mk

OBJDIR = obj/linux
OUTDIR = .
OUTNAME = crisscross-test
OUTBIN = $(OUTNAME)

SOURCES = \
main.cpp \
header.cpp

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

CCDV = ../tools/ccdv/ccdv.bin
ifneq ($(CC_BUILDSTATIC),yes)
LINK += -rdynamic
else
LINK += -L../source
endif
INCLUDES += -I. -I../source
CXXFLAGS += $(INCLUDES)

ifeq ($(GCC_MAJOR),4)
PCH = header.h.gch
endif

all: .depend precomp $(OUTDIR)/$(OUTBIN)

precomp: $(PCH)

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
	@$(CCDV) $(LINK) $+ -lpthread -lstdc++ -L../source -lcrisscross -o $(OUTDIR)/$(OUTBIN)
	@ln -sf ../source/$(LIBNAME).$(VERSION) $(LIBNAME)
	@ln -sf ../source/$(LIBNAME).$(VERSION) $(LIBNAME).$(VERSION_MAJOR)
	@ln -sf ../source/$(LIBNAME).$(VERSION) $(LIBNAME).$(VERSION)
else
	@ln -sf ../source/$(LIBNAME) $(LIBNAME)
	@$(CCDV) $(LINK) $+ -lpthread -lstdc++ libcrisscross-$(VERSION).a -o $(OUTDIR)/$(OUTBIN)
endif
ifneq ($(GCC_ISEMULATED),yes)
	@$(NM) $(OUTDIR)/$(OUTBIN) > $(OUTDIR)/$(OUTBIN).map
endif   
	@$(STRIP) $(OUTDIR)/$(OUTBIN)

$(PCH): header.h
	@$(CXX) -c header.h -o $(PCH) $(CXXFLAGS)


$(OBJDIR)/%.o: %.cpp precomp
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@$(CCDV) $(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c precomp
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@$(CCDV) $(CC) $(CXXFLAGS) -c $< -o $@

.depend:
ifeq ($(GCC_ISEMULATED),yes)
	@../contrib/fastdep-0.15/fastdep $(INCLUDES) --remakedeptarget=.depend $(SOURCES) > .depend
endif

ifneq ($(MAKECMDGOALS),clean)	
-include .depend
endif


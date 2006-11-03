OBJDIR = obj/linux
OUTDIR = .
OUTNAME = ccdv
OUTBIN = $(OUTNAME).bin

SOURCES = \
ccdv.c

OBJECTS = $(SOURCES:%.cpp=$(OBJDIR)/%.o)

CXX = g++
CC = gcc
LINK = $(CXX) -rdynamic
INCLUDES = -I.
CXXFLAGS = -O2 -Wall $(INCLUDES) -g
NM = :
STRIP = strip

all: .depend $(OUTDIR)/$(OUTBIN)

clean:
	rm -rf obj
	rm -f .depend
	rm -rf .libs
	rm -f $(OUTDIR)/$(OUTBIN)
	rm -f $(OUTDIR)/$(OUTBIN).map
	
$(OUTDIR)/$(OUTBIN): $(OBJECTS)
	@echo -n "Linking... "
	@$(LINK) $+ -o $(OUTDIR)/$(OUTBIN)
	@$(NM) $(OUTDIR)/$(OUTBIN) > $(OUTDIR)/$(OUTBIN).map
	@$(STRIP) $(OUTDIR)/$(OUTBIN)
	@echo done.

$(OBJDIR)/%.o: %.cpp
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@echo Compiling $<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@echo Compiling $<
	@$(CC) $(CXXFLAGS) -c $< -o $@

.depend:
	@echo Generating dependency information...
	@../../contrib/fastdep-0.15/fastdep $(CXXFLAGS) --remakedeptarget=.depend $(SOURCES) > .depend

ifneq ($(MAKECMDGOALS),clean)	
-include .depend
endif


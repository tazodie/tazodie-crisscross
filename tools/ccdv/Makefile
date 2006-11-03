include ../../common.mk

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

all: $(OUTDIR)/$(OUTBIN)

clean:
	rm -rf obj
	rm -rf .libs
	rm -f $(OUTDIR)/$(OUTBIN)
	rm -f $(OUTDIR)/$(OUTBIN).map
	
$(OUTDIR)/$(OUTBIN): $(OBJECTS)
	@$(LINK) $+ -o $(OUTDIR)/$(OUTBIN)
	@$(NM) $(OUTDIR)/$(OUTBIN) > $(OUTDIR)/$(OUTBIN).map
	@$(STRIP) $(OUTDIR)/$(OUTBIN)

$(OBJDIR)/%.o: %.cpp
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.c
	@test -d $(dir $(OBJDIR)/$<) || mkdir -p $(dir $(OBJDIR)/$<)
	@$(CC) $(CXXFLAGS) -c $< -o $@

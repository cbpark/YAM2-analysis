SRCDIR 	 := src
BINDIR   := bin
CXXFLAGS := -g -O2 -Wall -Wextra -std=c++14 -pedantic -I$(SRCDIR) $(CXXFLAGS)
LDFLAGS  := -O2
MKDIR    := mkdir -p
RM       := rm -f

# Targets
EXE    := $(BINDIR)/yam2analysis.exe
EXESRC := $(patsubst $(BINDIR)/%,$(SRCDIR)/%.cc,$(EXE))
EXEOBJ := $(EXESRC:.cc=.o)
LIBSRC := $(filter-out $(EXESRC),$(wildcard $(SRCDIR)/*.cc))
LIBOBJ := $(LIBSRC:.cc=.o)

# colevent (https://github.com/cbpark/colevent)
COLEVENT ?= /usr/local
CXXFLAGS += -I$(COLEVENT)/include/colevent
LDFLAGS  += -L$(COLEVENT)/lib -lcolevent -Wl,-rpath $(COLEVENT)/lib

# YAM2 (https://github.com/cbpark/YAM2)
YAM2     ?= ../YAM2
CXXFLAGS += -I$(YAM2)/src
# LDFLAGS  += -L$(YAM2)/lib -lYAM2

.PHONY: all clean

all: $(EXE)

$(BINDIR)/%.exe: $(SRCDIR)/%.o $(LIBOBJ)
	$(MKDIR) $(BINDIR)
	$(CXX) $(LDFLAGS) -o $@ $^

clean::
	$(RM) $(EXE) $(LIBOBJ)
	$(RM) -r $(BINDIR)

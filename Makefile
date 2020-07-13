SRCDIR 	 := src
BINDIR   := bin
CXXFLAGS := -g -O2 -Wall -Wextra -std=c++17 -pedantic -I$(SRCDIR) $(CXXFLAGS)
LIBS     :=
RM       := rm -f

# Targets
EXE    := $(BINDIR)/m2xx_sqp.exe \
	  $(BINDIR)/m2cx_sqp.exe \
	  $(BINDIR)/m2xc_sqp.exe \
	  $(BINDIR)/m2cc_sqp.exe \
	  $(BINDIR)/m2cr_sqp.exe \
	  $(BINDIR)/m2xx_mw_sqp.exe \
	  $(BINDIR)/m2cx_mw_sqp.exe \
	  $(BINDIR)/m2xc_mw_sqp.exe \
	  $(BINDIR)/m2cc_mw_sqp.exe \
	  $(BINDIR)/m2cr_mw_sqp.exe \
	  $(BINDIR)/m2xx_auglag_bfgs.exe \
	  $(BINDIR)/m2cx_auglag_bfgs.exe \
	  $(BINDIR)/m2xc_auglag_bfgs.exe \
	  $(BINDIR)/m2cc_auglag_bfgs.exe \
	  $(BINDIR)/m2cr_auglag_bfgs.exe \
	  $(BINDIR)/m2cc_mw_auglag_bfgs.exe \
	  $(BINDIR)/m2xx_auglag_nmsimplex.exe \
	  $(BINDIR)/m2cx_auglag_nmsimplex.exe \
	  $(BINDIR)/m2xc_auglag_nmsimplex.exe \
	  $(BINDIR)/m2cc_auglag_nmsimplex.exe \
	  $(BINDIR)/m2cr_auglag_nmsimplex.exe \
	  $(BINDIR)/m2cc_mw_auglag_nmsimplex.exe \
	  $(BINDIR)/mt2.exe
EXESRC := $(patsubst $(BINDIR)/%.exe,$(SRCDIR)/%.cc,$(EXE))
EXEOBJ := $(EXESRC:.cc=.o)
LIBSRC := $(filter-out $(EXESRC),$(wildcard $(SRCDIR)/*.cc))
LIBOBJ := $(LIBSRC:.cc=.o)

# colevent (https://github.com/cbpark/colevent)
COLEVENT ?= /usr/local
CXXFLAGS += -I$(COLEVENT)/include/colevent
LIBS     += -L$(COLEVENT)/lib -lcolevent -Wl,-rpath $(COLEVENT)/lib

# NLopt (https://nlopt.readthedocs.io/
NLOPT    ?= /usr
CXXFLAGS += -I$(NLOPT)/include
LIBS     += -L$(NLOPT)/lib -lnlopt

# YAM2 (https://github.com/cbpark/YAM2)
YAM2     ?= ../YAM2
CXXFLAGS += -I$(YAM2)/src
LIBS     += -L$(YAM2)/lib -lYAM2

.PHONY: all clean

all: $(EXE)

$(BINDIR)/%.exe: $(SRCDIR)/%.o $(LIBOBJ)
	$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS)

clean::
	$(RM) $(EXE) $(LIBOBJ)

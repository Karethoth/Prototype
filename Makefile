SRCDIR = src
OBJDIR = obj
BINDIR = bin

DIRS = $(OBJDIR) $(BINDIR)

LIBS = 

CXXTESTGEN = ../../cxxtest/bin/cxxtestgen
CXXTESTFLAGS = --error-printer

CC    = g++ -g
CWARN = -W -Wall -Wshadow -Wimplicit -Wreturn-type -Wformat -Wparentheses -Wpointer-arith -Wuninitialized -O

CFLAGS = -std=c++11

TGT     = prototype
TESTTGT = runTests


OBJS=\
     $(OBJDIR)/game/componentDataModels/positionComponent.o \
     $(OBJDIR)/game/scenes/introScene.o \
     $(OBJDIR)/game/components.o \
     $(OBJDIR)/engine/managers/meshManager.o \
     $(OBJDIR)/engine/managers/sceneManager.o \
     $(OBJDIR)/engine/scene.o \
     $(OBJDIR)/engine/mesh.o \
     $(OBJDIR)/engine/entitySystem.o 

MAINOBJ=\
     $(OBJDIR)/main.o


TESTS=\
	$(OBJDIR)/tests/entitySystemTestSuite.test.cc


all: $(TGT) $(TESTTGT)

 
$(TGT): $(DIRS) $(BINDIR)/$(TGT)
	cp $(BINDIR)/$(TGT) $(TGT)
	@echo "$@ up to date"


$(BINDIR)/$(TGT): $(OBJS) $(MAINOBJ)
	$(CC) $(LIBS) $(CFLAGS) -o $@ $(OBJS) $(MAINOBJ)

$(OBJDIR)/tests/%.test.cc: $(SRCDIR)/tests/%.cc
	$(CXXTESTGEN) $(CXXTESTFLAGS) -o $@ $?

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CC) $(CFLAGS) -c -o $@ $?

$(BINDIR):
	@mkdir $(BINDIR)

$(OBJDIR):
	@mkdir $(OBJDIR)
	@mkdir $(OBJDIR)/tests
	@mkdir $(OBJDIR)/game
	@mkdir $(OBJDIR)/game/componentDataModels
	@mkdir $(OBJDIR)/game/scenes
	@mkdir $(OBJDIR)/engine
	@mkdir $(OBJDIR)/engine/managers
	@mkdir $(OBJDIR)/engine/stacks

clean:
	rm -rf $(BINDIR)
	rm -rf $(OBJDIR)
	rm -rf $(TGT)

fresh: clean all


$(TESTTGT): $(OBJS) $(TESTS)
	$(CC) $(LIBS) $(CFLAGS) -o $@ $(OBJS) $(TESTS)


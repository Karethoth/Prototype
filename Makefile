SRCDIR = src
OBJDIR = obj
BINDIR = bin

DIRS = $(OBJDIR) $(BINDIR)

LIBS = -pthread -lglfw -lGLEW -lGL -lGLU
WINLIBS = -pthread -lglfw -lglew32s -lopengl32 -lglu32

CXXTESTGEN = ../../cxxtest/bin/cxxtestgen
CXXTESTFLAGS = --error-printer

CC    = g++
CWARN = -W -Wall -Wshadow -Wimplicit -Wreturn-type -Wformat -Wparentheses -Wpointer-arith -Wuninitialized -O

CFLAGS = -std=c++11 -g

TGT     = prototype
TESTTGT = runTests


OBJS=\
     $(OBJDIR)/game/componentDataModels/positionComponent.o \
     $(OBJDIR)/game/componentDataModels/rotationComponent.o \
     $(OBJDIR)/game/componentDataModels/autoRotationComponent.o \
     $(OBJDIR)/game/componentDataModels/velocityComponent.o \
     $(OBJDIR)/game/componentDataModels/meshComponent.o \
     $(OBJDIR)/game/systems/movementSystem.o \
     $(OBJDIR)/game/systems/renderSystem.o \
     $(OBJDIR)/game/systems/rotationSystem.o \
     $(OBJDIR)/game/scenes/introScene.o \
     $(OBJDIR)/game/components.o \
     $(OBJDIR)/engine/managers/meshManager.o \
     $(OBJDIR)/engine/managers/objManager.o \
     $(OBJDIR)/engine/managers/sceneManager.o \
     $(OBJDIR)/engine/mesh.o \
     $(OBJDIR)/engine/obj.o \
     $(OBJDIR)/engine/message.o \
     $(OBJDIR)/engine/scene.o \
     $(OBJDIR)/engine/baseSystem.o \
     $(OBJDIR)/engine/entitySystem.o 

MAINOBJ=\
     $(OBJDIR)/main.o


TESTS=\
	$(OBJDIR)/tests/entitySystemTestSuite.test.cc


all: $(TGT) #$(TESTTGT)


win:
	mingw32-make LIBS="$(WINLIBS)"

 
$(TGT): $(DIRS) $(BINDIR)/$(TGT)
	@cp $(BINDIR)/$(TGT) $(TGT)
	@echo ""
	@echo "$@ up to date"
	@echo ""


$(BINDIR)/$(TGT): $(OBJS) $(MAINOBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(MAINOBJ) $(LIBS)

$(OBJDIR)/tests/%.test.cc: $(SRCDIR)/tests/%.cc
	$(CXXTESTGEN) $(CXXTESTFLAGS) -o $@ $?

$(OBJDIR)/%.o: $(SRCDIR)/%.cc
	$(CC) $(CFLAGS) -c -o $@ $?

$(BINDIR):
	@mkdir $(BINDIR)

$(OBJDIR):
	python mkdir.py $(OBJDIR)
	python mkdir.py $(OBJDIR)/tests
	python mkdir.py $(OBJDIR)/game
	python mkdir.py $(OBJDIR)/game/componentDataModels
	python mkdir.py $(OBJDIR)/game/systems
	python mkdir.py $(OBJDIR)/game/scenes
	python mkdir.py $(OBJDIR)/engine
	python mkdir.py $(OBJDIR)/engine/managers
	python mkdir.py $(OBJDIR)/engine/stacks

clean:
	rm -rf $(OBJDIR)
	rm -rf $(BINDIR)
	rm -rf $(TGT)

fresh: clean all


$(TESTTGT): $(OBJS) $(TESTS)
	$(CC) $(LIBS) $(CFLAGS) -o $@ $(OBJS) $(TESTS)


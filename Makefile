# Generic project Makefile

EXECUTABLE = scivis	

SIMULATION	=	simulation/diffusematter.o \
				simulation/setforces.o \
				simulation/simulation0.o \
				simulation/simulation1.o \
				simulation/simulationstep.o \
				simulation/solve.o

UTILITY		=	utility/clamp.o \
				utility/readfile.o

WINDOW		=	window/directiontocolor.o \
				window/framebufferresized.o \
				window/keyevent.o \
				window/mousebuttonevent.o \
				window/mousemoved.o \
				window/paintsmoke.o \
				window/paintvectors.o \
				window/repaint.o \
				window/setcolormap.o \
				window/setinputcallbacks.o \
				window/window0.o \
				window/window1.o

OBJECTS		=	$(GLAD) \
				$(RENDERER) \
				$(SIMULATION) \
				$(UTILITY) \
				$(WINDOW) \
				main.o

#build macros
COMPILER = g++
FLAGS = -std=c++17 -Wall -ggdb -pedantic
INCLUDEDIRS = -I./fftw/include/
LIBDIRS     = -L./fftw/lib/
LIBRARIES = $(LIBDIRS) -lrfftw -lfftw -lGL -lGLU -lGLEW -lm -lglut

#folders
SOURCEDIR = src
BUILDDIR = build

#executable build
$(EXECUTABLE): folders $(addprefix $(BUILDDIR)/,$(OBJECTS))
	$(COMPILER) $(FLAGS) $(addprefix $(BUILDDIR)/,$(OBJECTS)) -o $@ $(LIBRARIES)

#optional include of dependencies
-include $(addprefix $(BUILDDIR)/,$(OBJECTS:.o=.d))

#phony for rules that should never have a corresponding file
.PHONY: folders clean gdb run rebuild

# guarantees that all required folders exist
folders:
	@mkdir -p build
	@mkdir -p $(filter-out %./,$(addprefix $(BUILDDIR)/,$(dir $(OBJECTS))))

clean:
	rm -f $(EXECUTABLE)
	rm -rf build/
	make folders

rebuild:
	make clean
	make -j 12

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(COMPILER) $(FLAGS) $(INCLUDEDIRS) -o $@ -c $<
	@$(COMPILER) $(FLAGS) -MM -MT $(BUILDDIR)/$*.o src/$*.cpp > $(BUILDDIR)/$*.d

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cc
	$(COMPILER) $(FLAGS) $(INCLUDEDIRS) -o $@ -c $<
	@$(COMPILER) $(FLAGS) -MM -MT $(BUILDDIR)/$*.o src/$*.cc > $(BUILDDIR)/$*.d

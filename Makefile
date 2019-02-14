# Generic project Makefile

EXECUTABLE = scivis	

OBJECTS			=	clamp.o \
					diffusematter.o \
					directiontocolor.o \
					display.o \
					drag.o \
					FFT.o \
					globals.o \
					initsimulation.o \
					keyboard.o \
					main.o \
					rainbow.o \
					reshape.o \
					setcolormap.o \
					setforces.o \
					simulationstep.o \
					solve.o \
					visualize.o

#build macros
COMPILER = g++
FLAGS = -std=c++17 -Wall -ggdb -pedantic
INCLUDEDIRS = -I./fftw-2.1.5/include/
LIBDIRS     = -L./fftw-2.1.5/lib/
LIBRARIES = $(LIBDIRS) -lrfftw -lfftw -lglut -lGL -lGLU -lGLEW -lm

#folders
SOURCEDIR = src
BUILDDIR = build

#executable build
$(EXECUTABLE): folders $(addprefix $(BUILDDIR)/,$(OBJECTS))
	$(COMPILER) $(FLAGS) $(addprefix $(BUILDDIR)/,$(OBJECTS)) -o $@ $(LIBRARIES) -m32

#optional include of dependencies
-include $(addprefix $(BUILDDIR)/,$(OBJECTS:.o=.d))

#phony for rules that should never have a corresponding file
.PHONY: folders clean gdb run rebuild

#@mkdir -p $(filter-out %./,$(addprefix $(BUILDDIR)/,$(dir $(OBJECTS))))
folders:
	@mkdir -p build

clean:
	rm -rf build/
	make folders

gdb: $(EXECUTABLE)
	gdb ./$(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

rebuild:
	make clean
	make -j 12

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	$(COMPILER) $(FLAGS) $(INCLUDEDIRS) -o $@ -c $< -m32
	@$(COMPILER) $(FLAGS) -MM -MT $(BUILDDIR)/$*.o src/$*.cpp > $(BUILDDIR)/$*.d

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cc
	$(COMPILER) $(FLAGS) $(INCLUDEDIRS) -o $@ -c $< -m32
	@$(COMPILER) $(FLAGS) -MM -MT $(BUILDDIR)/$*.o src/$*.cc > $(BUILDDIR)/$*.d
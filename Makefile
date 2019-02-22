# Generic project Makefile

EXECUTABLE = scivis	

GLAD				=	glad/glad.o

LINERENDERMODEL		=	linerendermodel/defaultcolors.o \
						linerendermodel/defaultlines.o \
						linerendermodel/framebuffersize.o \
						linerendermodel/linerendermodel1.o \
						linerendermodel/render.o \
						linerendermodel/setdata.o

RENDERMODEL			=	rendermodel/compileshader.o \
						rendermodel/linkprogram.o \
						rendermodel/rendermodel0.o

SIMULATION			=	simulation/diffusematter.o \
						simulation/setforces.o \
						simulation/simulation0.o \
						simulation/simulation1.o \
						simulation/simulationstep.o \
						simulation/solve.o

UTILITY				=	utility/clamp.o \
						utility/readfile.o

OBJECTS				=	$(GLAD) \
						$(LINERENDERMODEL) \
						$(RENDERMODEL) \
						$(SIMULATION) \
						$(UTILITY) \
						main.o
#build macros
COMPILER = g++
FLAGS = -std=c++17 -Wall -ggdb -pedantic
INCLUDEDIRS = -I./extern/include/
LIBDIRS     = -L./extern/lib/
LIBRARIES = $(LIBDIRS) -lrfftw -lfftw -lGL -lGLU -lGLEW -lm -lglfw

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

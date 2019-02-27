# Generic project Makefile

EXECUTABLE = scivis	

GLAD				=	glad/glad.o

LINERENDERMODEL		=	linerendermodel/linerendermodel0.o \
						linerendermodel/linerendermodel1.o \
						linerendermodel/render.o

RENDERMODEL			=	rendermodel/compileshader.o \
						rendermodel/framebuffersize.o \
						rendermodel/linkprogram.o \
						rendermodel/loadshaders.o \
						rendermodel/preparebuffers.o \
						rendermodel/setcolordata.o \
						rendermodel/setvertexdata.o \
						rendermodel/rendermodel1.o \
						rendermodel/rendermodel0.o

SIMULATION			=	simulation/diffusematter.o \
						simulation/setforces.o \
						simulation/simulation0.o \
						simulation/simulation1.o \
						simulation/simulationstep.o \
						simulation/solve.o

SMOKERENDERMODEL	=	smokerendermodel/render.o \
						smokerendermodel/smokerendermodel0.o \
						smokerendermodel/smokerendermodel1.o

TEXTRENDERER		=	textrenderer/loadglyphs.o \
						textrenderer/textrenderer1.o

UTILITY				=	utility/clamp.o \
						utility/readfile.o

WINDOW				=	window/colormappingstring.o \
						window/colormodestring.o \
						window/scalingmodestring.o \
						window/drawmodestring.o \
						window/framebufferresized.o \
						window/initializesmokerender.o \
						window/keyevent.o \
						window/mousebuttonevent.o \
						window/mousemoved.o \
						window/paintsmoke.o \
						window/paintvectors.o \
						window/printshortcuts.o \
						window/repaint.o \
						window/setdrawmode.o \
						window/setinputcallbacks.o \
						window/window0.o \
						window/window1.o

OBJECTS				=	$(GLAD) \
						$(LINERENDERMODEL) \
						$(RENDERMODEL) \
						$(SIMULATION) \
						$(SMOKERENDERMODEL) \
						$(TEXTRENDERER) \
						$(UTILITY) \
						$(WINDOW) \
						main.o
#build macros
COMPILER = g++
FLAGS = -std=c++17 -Wall -ggdb -pedantic -fopenmp
INCLUDEDIRS = -I./extern/include/
LIBDIRS     = -L./extern/lib/
LIBRARIES = $(LIBDIRS) -lrfftw -lfftw -lGL -lGLU -lGLEW -lm -lglfw -lfreetype

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

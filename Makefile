# Generic project Makefile

EXECUTABLE = scivis	

ARROW3DRENDERMODEL	=	arrow3drendermodel/arrow3drendermodel1.o \
						arrow3drendermodel/initialize.o \
						arrow3drendermodel/render.o \
						arrow3drendermodel/setarrowdim.o \
						arrow3drendermodel/updatescalar.o \
						arrow3drendermodel/updatevectors.o

ENUMS				=	enums/colormappingstring.o \
						enums/colormodestring.o \
						enums/drawmodestring.o \
						enums/scalingmodestring.o\
						enums/divmodestring.o\
						enums/glyphmodestring.o

GLAD				=	glad/glad.o \
						lodepng/lodepng.o

GLYPH2DRENDERMODEL	=	glyph2drendermodel/glyph2drendermodel1.o \
						glyph2drendermodel/initialize.o \
						glyph2drendermodel/render.o \
						glyph2drendermodel/setglyphdim.o \
						glyph2drendermodel/unitglyph.o \
						glyph2drendermodel/updatescalar.o \
						glyph2drendermodel/updatevectors.o

ISOLINE2DRENDERMODEL=	isoline2drendermodel/initialize.o \
						isoline2drendermodel/isoline2drendermodel1.o \
						isoline2drendermodel/render.o \
						isoline2drendermodel/updatelines.o

LINERENDERMODEL		=	linerendermodel/linerendermodel0.o \
						linerendermodel/linerendermodel1.o \
						linerendermodel/render.o

OBJREADER			=	objreader/extracttriangles.o \
						objreader/extractvertex.o \
						objreader/objreader1.o \
						objreader/parseface.o \
						objreader/parseindex.o \
						objreader/parsenormal.o \
						objreader/parsevertex.o \
						objreader/rawnormals.o \
						objreader/rawvertices.o

RENDERFONT			=	renderfont/buildmap.o \
						renderfont/createstring.o \
						renderfont/firstpass.o \
						renderfont/generatetexture.o \
						renderfont/renderfont0.o \
						renderfont/renderfont1.o \
						renderfont/renderfont2.o \
						renderfont/renderstring.o \
						renderfont/renderstringoutlined.o \
						renderfont/storeglyph.o \
						renderfont/swap.o \
						renderfont/texposition.o \
						renderfont/updatestring.o \
						renderfont/string/bufferstring.o \
						renderfont/string/generatebuffers.o \
						renderfont/string/operatorassign1.o \
						renderfont/string/string0.o \
						renderfont/string/string1.o \
						renderfont/string/string2.o \
						renderfont/string/swap.o

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

SMOKERENDERMODEL	=	smokerendermodel/buildbar.o \
						smokerendermodel/render.o \
						smokerendermodel/renderbar.o \
						smokerendermodel/smokerendermodel0.o \
						smokerendermodel/smokerendermodel1.o

UTILITY				=	utility/buildprogram.o \
						utility/clamp.o \
						utility/compileshader.o \
						utility/linkprogram.o \
						utility/linterp.o \
						utility/loadtexture.o \
						utility/readfile.o

WINDOW				=	window/framebufferresized.o \
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
						window/calcStore.o \
						window/calc_lines.o \
						window/window0.o \
						window/window1.o 

OBJECTS				=	$(ARROW3DRENDERMODEL) \
						$(ENUMS) \
						$(GLAD) \
						$(GLYPH2DRENDERMODEL) \
						$(ISOLINE2DRENDERMODEL) \
						$(LINERENDERMODEL) \
						$(OBJREADER) \
						$(RENDERFONT) \
						$(RENDERMODEL) \
						$(SMOKERENDERMODEL) \
						$(UTILITY) \
						$(WINDOW) \
						main.o
#build macros
COMPILER = g++
# FLAGS = -std=c++17 -Wall -ggdb -pedantic -fopenmp
FLAGS = -std=c++17 -Wall -g -fopenmp
INCLUDEDIRS = -I./extern/include/
LIBDIRS     = -L./extern/lib/
LIBRARIES = $(LIBDIRS) -lfftw3 -lGL -lglfw -lfreetype -ldl

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

########################################################################
############################ Makefile ##################################
########################################################################

# Currently this makefile only supports a very restrictive workflow on
# Windows as I'm only using it for learning purposes
# Worflow :
# 		- clang-cl in PATH
#		- cygwin bin folder in PATH
#
# With these two requirements met, the code should compile just fine

# Compiler settings
CXX = clang-cl
CXXFLAGS = /std:c++latest
DPSFLAGS = /clang:-MMD
LDFLAGS = 

# Makefile settings
APPNAME = chap4.exe
EXT = .cxx
SRCDIR = src
INCLDIR = include
OBJDIR = obj

SRC = $(wildcard $(SRCDIR)/*$(EXT))
OBJ = $(SRC:$(SRCDIR)/%$(EXT)=$(OBJDIR)/%.o)
DEP = $(OBJ:$(OBJDIR)/%.o=$(OBJDIR)/%.d)

RM = rm
DELOBJ = $(OBJ)

########################################################################
####################### Targets beginning here #########################
########################################################################

all: create_obj_dir $(APPNAME)

create_obj_dir:
	@mkdir -p $(OBJDIR)

# Builds the app
$(APPNAME): $(OBJ)
	echo $^
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) /o $@ 

# Creates the dependency rules
$(OBJDIR)/%.d: $(SRCDIR)/%$(EXT)
	$(CXX) $(CXXFLAGS) /I $(INCLDIR) /clang:-MM /clang:"-MT $(@:$(OBJDIR)/%.d=$(OBJDIR)/%.o)" $< > $@

# Includes all .hxx files
-include $(DEP)

# Building rule for .o files and its .cxx in combination with all .hxx
$(OBJDIR)/%.o: $(SRCDIR)/%$(EXT)
	$(CXX) $(CXXFLAGS) /I $(INCLDIR) /o $@ /c $< /EHs

######################### Cleaning rules ###########################
# Cleans complete project
.PHONY: clean
clean:
	echo "Cleaning project..."
	@-$(RM) $(DELOBJ) $(DEP) $(APPNAME)

# Cleans only all files with the extension .d
.PHONY: cleandep
cleandep:
	$(RM) $(DEP)


.PHONY: re
re: clean all

.PHONY: run
run: 
	./$(basename $(APPNAME))
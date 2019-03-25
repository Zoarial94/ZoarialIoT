#Standard Compiling Options
CXX := gcc
SRCDIR := src
BUILDDIR := build
INCDIR := include
TARGET := bin/main
DEPDIR := dep

#Testing Compiling Options
TESTSRCDIR := test
TESTBUILDDUR := test/build
TESTTARGET := bin/test

#Standard Compiling Files and Arguments
SRCEXT := cpp
INCEXT := hpp
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPENDENCIES := $(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SOURCES:.$(SRCEXT)=.d))
LIB := -lpthread -ldl -lstdc++ -ltins -lconfig4cpp
LIBDIR := -L~/Documents/Libraries/ 
CXXFLAGS := -Wall
INC := -I include

#Testing Compiling Files and Arguments
TESTSOURCES := $(shell find $(TESTSRCDIR) -type f -name "*.$(SRCEXT)")
TESTOBJECTS := $(patsubst $(TESTSRCDIR)/%,$(TESTBUILDDIR)/%,$(TESTSOURCES:.$(SRCEXT)=.o))

MAINOBJS := $(OBJECTS) $(BUILDDIR)/main.o
EXAMOBJS := $(OBJECTS) $(BUILDDIR)/example.o


#Compile Target
$(TARGET): $(MAINOBJS)
	@echo " Linking... $(MAINOBJS)"
	$(CXX)  $^ -o $(TARGET) $(LIB) $(LIBDIR) $(CXXFLAGS)

#Include dependencies which are created
#-include $(DEPENDENCIES:)
#include $(DEPENDENCIES)

#Create object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) include/%.hpp 
#Make build directory
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(DEPDIR)
#Compile object
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

$(BUILDDIR)/%.o: ./%.$(SRCEXT) 
#Make build directory
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(DEPDIR)
#Compile object
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<

#Clean
clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(DEPDIR) $(TARGET)

.PHONY: clean

#Basic example
Example: $(EXAMOBJS)
	



#Prevents failure if dependency does not exist
#$(DEPDIR)/%.d: ;
#.PRECIOUS: $(DEPDIR)/%.d


#Standard Compiling Options
CXX := g++
SRCDIR := src
BUILDDIR := build
INCDIR := include
TARGET := bin/main
DEPDIR := dep

#Testing Compiling Options
TESTSRCDIR := tests
TESTBUILDDUR := tests/build
TESTTARGET := bin/test

#Standard Compiling Files and Arguments
SRCEXT := cpp
INCEXT := hpp
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
DEPENDENCIES := $(patsubst $(SRCDIR)/%,$(DEPDIR)/%,$(SOURCES:.$(SRCEXT)=.d))
LIB := -lpthread -ldl -lstdc++ -ltins -lconfig++ -lpcap
LIBDIR := -L~/Libraries/ 
CXXFLAGS := -Wall -Werror -std=c++17 -g
INC := -I include

#Testing Compiling Files and Arguments
TESTSOURCES := $(shell find $(TESTSRCDIR) -type f -name "*.$(SRCEXT)")
TESTOBJECTS := $(patsubst $(TESTSRCDIR)/%,$(TESTBUILDDIR)/%,$(TESTSOURCES:.$(SRCEXT)=.o))

MAINOBJS := $(OBJECTS) #$(BUILDDIR)/main.o
EXAMOBJS := $(OBJECTS) $(BUILDDIR)/example.o


#Compile Target
$(TARGET): $(MAINOBJS)
	@echo " Linking... $(MAINOBJS)"
	$(CXX)  $^ -o $(TARGET) $(LIB) $(LIBDIR) $(CXXFLAGS)

#Include dependencies which are created
#-include $(DEPENDENCIES:)
include $(wildcard $(DEPENDENCIES))

#Create object files
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
#Make build directory
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(DEPDIR)
#Make Makefiles
	$(CXX) $(CXXFLAGS) $(INC) -MT $@ -MM -MP $< > $(DEPDIR)/$*.Td
	@cd $(DEPDIR); \
	cp $*.Td $*.d; \
    sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $*.Td >> $*.d; \
	rm -f $*.Td; \
	cd ../;
#Compile object
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
#Fancy deleting/copying
#Handles files that no longer exist
	@cp -f $(DEPDIR)/$*.d $(DEPDIR)/$*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $(DEPDIR)/$*.d.tmp | fmt -1 | \
	sed -e 's/^ *//' -e 's/$$/:/' >> $(DEPDIR)/$*.d
	@rm -f $(DEPDIR)/$*.d.tmp


#Clean
clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(DEPDIR) $(TARGET)

.PHONY: clean

#Basic example
Example: $(EXAMOBJS)
	



#Prevents failure if dependency does not exist
$(DEPDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d


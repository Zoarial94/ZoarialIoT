#Standard Compiling Options
CXX := gcc
SRCDIR := src
BUILDDIR := build
INCDIR := include
TARGET := bin/main

#Testing Compiling Options
TESTSRCDIR := test
TESTBUILDDUR := test/build
TESTTARGET := bin/test

#Standard Compiling Files and Arguments
SRCEXT := cpp
INCEXT := hpp
SOURCES := $(shell find $(SRCDIR) -type f -name "*.$(SRCEXT)")
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
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
	@echo " Linking... $(OBJECTS)"
	$(CXX)  $^ -o $(TARGET) $(LIB) $(LIBDIR) $(CXXFLAGS)

#Include dependencies which are created
-include $(OBJECTS:.o=.d)

#Create object files
$(BUILDDIR)/%.o: %.$(SRCEXT)
$(BUILDDIR)/%.o: %.$(SRCEXT) $(BUILDDIR)/%.d
#Make build directory
	@mkdir -p $(BUILDDIR)
#Compile object
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
#Make dependency list/object
	$(CXX) $(CXXFLAGS) $(INC) -MM $< > $(BUILDDIR)/$*.d
#Fancy deleting/copying
#Handles files that no longer exist
	@cp -f $(BUILDDIR)/$*.d $(BUILDDIR)/$*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.d
	@rm -f $(BUILDDIR)/$*.d.tmp

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT) $(BUILDDIR)/%.d
#Make build directory
	@mkdir -p $(BUILDDIR)
#Compile object
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
#Make dependency list/object
	$(CXX) $(CXXFLAGS) $(INC) -MM $< > $(BUILDDIR)/$*.d
#Fancy deleting/copying
#Handles files that no longer exist
	@cp -f $(BUILDDIR)/$*.d $(BUILDDIR)/$*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.d
	@rm -f $(BUILDDIR)/$*.d.tmp

$(BUILDDIR)/%.o: test/%.$(SRCEXT)
$(BUILDDIR)/%.o: test/%.$(SRCEXT) $(BUILDDIR)/%.d
#Make build directory
	@mkdir -p $(BUILDDIR)
#Compile object
	$(CXX) $(CXXFLAGS) $(INC) -c -o $@ $<
#Make dependency list/object
	$(CXX) $(CXXFLAGS) $(INC) -MM $< > $(BUILDDIR)/$*.d
#Fancy deleting/copying
#Handles files that no longer exist
	@cp -f $(BUILDDIR)/$*.d $(BUILDDIR)/$*.d.tmp
	@sed -e 's/.*://' -e 's/\\$$//' < $(BUILDDIR)/$*.d.tmp | fmt -1 | \
	  sed -e 's/^ *//' -e 's/$$/:/' >> $(BUILDDIR)/$*.d
	@rm -f $(BUILDDIR)/$*.d.tmp


#Clean
clean:
	@echo " Cleaning..."; 
	$(RM) -r $(BUILDDIR) $(TARGET)

.PHONY: clean

#Basic example
Example: $(EXAMOBJS)
	



#Prevents failure if dependency does not exist
$(BUILDDIR)/%.d: ;
.PRECIOUS: $(DEPDIR)/%.d


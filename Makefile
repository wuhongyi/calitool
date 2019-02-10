OBJ = cali

CXX=g++        
CXXFLAGS:=-std=c++11 -g -Wall -lrt  -I. 
ROOTLIBS = $(shell root-config --libs) -lGui
ROOTINC = -I$(shell root-config --incdir) 
CXXFLAGS+=$(ROOTINC)
LIBS:=



INCLUDES:=caliMainFrame.hh

OBJECTS:=caliMainFrame.o main.o MainDict.o

SRCS:=caliMainFrame.cc main.cc MainDict.cc

all: $(OBJ)


$(OBJ): $(SRCS) $(OBJECTS) $(INCLUDES)
	$(CXX) -o  $@  $(OBJECTS) $(CXXFLAGS) $(LIBS) $(ROOTLIBS)

%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -c $< 
%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< 
MainDict.cc:caliMainFrame.hh caliLinkDef.h
	rootcint -f $@ -c $^


clean: 
	rm -f *.o *~ $(OBJ) *Dict*

very-clean:
	rm -f $(OBJ) *.o *~

.PHONY: clean very-clean
#.SILENT:

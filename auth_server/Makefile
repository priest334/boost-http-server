###########################################
# A Simple Makefile
###########################################

NMARCH	=$(subst _,-,$(shell uname -m))

#CXX		= g++
CXXFLAGS= -g -Wall -Wno-deprecated -march=$(NMARCH)

APPNAME	= $(shell pwd|awk -F'/' '{print $$NF}')

CONDFLAGS = 

INCLUDES:= -I.
LINKLIBS:= -lpthread -lboost_thread -lboost_program_options

COMPILEFLAGS:=$(CXXFLAGS) $(CONDFLAGS)
LINKFLAGS:=

ALLDIRS	= $(shell find . -name '*' -type d)
DIRFILES= $(wildcard $(dir)/*.cpp)
ALLFILES:= $(foreach dir,$(ALLDIRS),$(DIRFILES))

SOURCES	:= $(ALLFILES)
OBJECTS := $(SOURCES:.cpp=.o)

.PHONY:all clean

all:$(APPNAME)
$(APPNAME): $(OBJECTS)
	$(CXX) $(LINKFLAGS) -o $@ $^ $(LINKLIBS)
	chmod a+x $(APPNAME)

$(OBJECTS):%.o:%.cpp
	$(CXX) $(COMPILEFLAGS) $(INCLUDES) -c $^ -o $@
	
clean:
	rm -f $(APPNAME) $(OBJECTS)

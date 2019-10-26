
INCLUDE := -I ./include -I ./lib/sha256
LIBS := $(shell find $(LIBDIR) -name '*.cpp')
SOURCES := $(shell find $(SOURCEDIR) -name '*.cpp')

all:
	g++ -std=c++11 $(SOURCES) $(LIB) $(INCLUDE) -o blockchain
#(Only tested on Windows And MacOS)
# Ref:https://www.gnu.org/software/make/manual/html_node/index.html#Top
ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell uname -s)
endif
#################### Windows ####################
ifeq ($(detected_OS),Windows)
CXX = g++
OBJDIR = obj/windows
SRCDIR = src
EXE = essay-search
CXXFLAGS = -std=c++17 -lstdc++fs

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all dbg clean run run-dbg 

all: $(OBJECTS)
	$(CXX) -o $(EXE).exe $(OBJECTS) $(CXXFLAGS)
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
clean:
	del $(EXE).exe $(OBJDIR)/*.o
run:
	make all
	./$(EXE).exe
endif
#################### Linux ####################
ifeq ($(detected_OS),Linux)
# sudo apt-get update
CXX = g++
OBJDIR = obj/linux
SRCDIR = src
EXE = essay-search
CXXFLAGS = -std=c++17 -lstdc++fs

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

.PHONY: all

all: $(OBJECTS)
	$(CXX) -o $(EXE) $(OBJECTS) $(CXXFLAGS)
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
clean:
	rm $(EXE) $(OBJECTS)
run:
	make all
	./$(EXE)
endif
#################### MacOS ####################
ifeq ($(detected_OS),Darwin)
# brew install make
CXX = g++
OBJDIR = obj/macos
EXE = essay-search

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(SRCDIR)/*.hpp)
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

CXXFLAGS = -std=c++17 -lstdc++fs

.PHONY: all clean run

all: $(OBJECTS)
	$(CXX) -o $(EXE) $(OBJECTS) $(CXXFLAGS)
$(OBJECTS): $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
clean:
	rm -rf $(EXE) $(OBJECTS)
run:
	make all
	./$(EXE)
endif
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
ODIR = obj\windows
EXE = essay-search

SRC  := $(wildcard *.cpp)
OBJ  := $(SRC:%.cpp=$(ODIR)\\%.o)

CXXFLAGS = -std=c++17 -lstdc++fs

.PHONY: all dbg clean run run-dbg 

all: $(OBJ)
	$(CXX) -o $(EXE).exe $(OBJ) $(CXXFLAGS)
%.o: %.cpp
	$(CXX) -c $< -o $(ODIR)\$@ $(CXXFLAGS) 
$(OBJ): $(ODIR)\\%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
dbg:
	$(CXX) -g $(SRC) -o $(EXE)_dbg.exe $(CXXFLAGS) 
clean:
	del $(EXE).exe $(EXE)_dbg.exe $(ODIR)\*.o
run:
	make all
	.\\$(EXE).exe
run-dbg:
	make dbg
	gdb .\\$(EXE)_dbg.exe

endif
#################### Linux ####################
ifeq ($(detected_OS),Linux)
# sudo apt-get update
CXX = g++
ODIR = obj/linux
EXE = essay-search

SRC  := $(wildcard *.cpp)
OBJ  := $(SRC:%.cpp=$(ODIR)/%.o)

CXXFLAGS = -std=c++17 -lstdc++fs

.PHONY: all
all: $(OBJ)
	$(CXX) -o $(EXE) $(OBJ) $(CXXFLAGS)
%.o: %.cpp
	$(CXX) -c $< -o $(ODIR)/$@ $(CXXFLAGS)
$(OBJ): $(ODIR)/%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
clean:
	rm $(EXE) $(OBJ)
run:
	make all
	./$(EXE)
endif
#################### MacOS ####################
ifeq ($(detected_OS),Darwin)
# brew install make
# brew install allegro
# brew install pkg-config
CXX = g++
ODIR = obj/macos
EXE = essay-search

SRC  := $(wildcard *.cpp)
OBJ  := $(SRC:%.cpp=$(ODIR)/%.o)

CXXFLAGS = -std=c++17 -lstdc++fs

.PHONY: all clean run
all: $(OBJ)
	$(CXX) -o $(EXE) $(OBJ) $(CXXFLAGS)
%.o: %.cpp
	$(CXX) -c $< -o $(ODIR)/$@ $(CXXFLAGS)
$(OBJ): $(ODIR)/%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)
clean:
	rm -rf $(OBJ) $(EXE)
run:
	make all
	./$(EXE)
endif
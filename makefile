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
ODIR = obj\linux
EXE = TowerDefense

SRC  := $(wildcard *.cpp)
OBJ  := $(SRC:%.cpp=$(ODIR)/%.o)
ALLEGRO_LIBRARIES := allegro-5 allegro_main-5 allegro_font-5 allegro_color-5 allegro_image-5 allegro_acodec-5 allegro_audio-5 allegro_dialog-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5 allegro_video-5
ALLEGRO_FLAGS := $(shell pkg-config --cflags --libs $(ALLEGRO_LIBRARIES))

CXXFLAGS = -std=c++11 -O2
LDFLAGS = -lm -Wall -Wextra

.PHONY: all
all: $(OBJ)
	$(CXX) -o $(EXE) $(OBJ) $(ALLEGRO_FLAGS) $(CXXFLAGS) $(LDFLAGS)
%.o: %.cpp
	$(CXX) -c $< -o $(ODIR)/$@ $(ALLEGRO_FLAGS) $(CXXFLAGS)
$(OBJ): $(ODIR)/%.o: %.cpp
	$(CXX) -c $< -o $@ $(ALLEGRO_FLAGS) $(CXXFLAGS)
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
ODIR = obj
EXE = TowerDefense

SRC  := $(wildcard *.cpp)
OBJ  := $(SRC:%.cpp=$(ODIR)/%.o)
CXXFLAGS = -std=c++11 -O2 `pkg-config allegro-5 --cflags`
LDFLAGS = -lm -Wall -Wextra
LDLIBS = `pkg-config allegro-5 allegro_acodec-5 allegro_audio-5 allegro_color-5 allegro_dialog-5 allegro_font-5 allegro_image-5 allegro_main-5 allegro_memfile-5 allegro_physfs-5 allegro_primitives-5 allegro_ttf-5 allegro_video-5 --libs`

.PHONY: all clean run
all: $(OBJ)
	$(CXX) -o $(EXE) $(OBJ) $(LDFLAGS) $(LDLIBS)
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
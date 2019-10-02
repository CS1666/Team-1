CPP_FILES = $(wildcard *.cpp)  
OUT_NAMES = $(patsubst %.cpp,%.o,$(CPP_FILES))
CC = clang++
COMPILER_FLAGS = -Wall -I/usr/include/SDL2
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(OUT_NAMES)

%.o: %.cpp gpEntity.o BasicMovementFPSlimit.o
	$(CC) $^ $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

gpEntity.o : ./General/gpEntity.cpp ./General/gpEntity.h
	$(CC) -c ./General/gpEntity.cpp $(COMPILER_FLAGS) 

BasicMovementFPSlimit.o : ./Physics/BasicMovementFPSlimit.cpp ./Physics/BasicMovementFPSlimit.h
	$(CC) -c ./Physics/BasicMovementFPSlimit.cpp $(COMPILER_FLAGS) 

clean:
	rm *.o

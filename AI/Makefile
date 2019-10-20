CPP_FILES = $(wildcard *.cpp)  
OUT_NAMES = $(patsubst %.cpp,%.o,$(CPP_FILES))
CC = clang++
COMPILER_FLAGS = -Wall -I/usr/include/SDL2 -std=c++11
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

all: $(OUT_NAMES)

%.o: %.cpp 
	$(CC) -c $^ $(COMPILER_FLAGS) 

clean:
	rm *.o

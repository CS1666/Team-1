CPP_FILES = $(wildcard *.cpp)  
OUT_NAMES = $(patsubst %.cpp,%.o,$(CPP_FILES))
FOLDERS = $(wildcard ./General/*.o)\
		$(wildcard ./Physics/*.o)
		#$(wildcard ./AI/*.o)\
		#$(wildcard ./Level Generation/*.o)\
		
CC = clang++
COMPILER_FLAGS = -Wall -I/usr/include/SDL2
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf


all: 
	+$(MAKE) -C AI
	+$(MAKE) -C General
	+$(MAKE) -C Physics
	+$(MAKE) -C 'Level Generation'
	+$(MAKE) main.o
	+$(MAKE) aipg.o
main.o: main.cpp 
	$(CC) $^ $(FOLDERS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

aipg.o : aipg.cpp
	$(CC) $^ $(FOLDERS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $@

clean:
	rm *.o
	rm $(FOLDERS)
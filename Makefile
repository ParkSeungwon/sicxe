CFLAG = -g -std=c++11 -fmax-errors=1 -ffunction-sections -fdata-sections
CC = g++
SRC = $(wildcard *.cc)
CPP = $(wildcard *.cpp)
EXE = $(patsubst %.cpp, %.x, $(CPP))
OBJ = $(patsubst %.cc, %.o, $(SRC))

all : $(OBJ) $(EXE) 

%.x : %.cpp $(OBJ) 
	$(CC) $< -o $@ $(OBJ) $(CFLAG) -Os -Wl,--gc-sections

%.o : %.cc %.h
	$(CC) $< -c $(CFLAG) 

clean :
	rm *.o *.x

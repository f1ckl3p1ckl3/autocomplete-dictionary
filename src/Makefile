# Define C compiler & flags
CC = gcc
CFLAGS = -Wall -g
# Define libraries to be linked (for example -lm)
LDLIBS = 

# Define sets of source files and object files
SRC = readCSV.c slicing.c linkedList.c main.c array.c compare.c tree.c
# OBJ is the same as SRC, just replace .c with 
OBJ = $(SRC:.c=.o)
 
# Define the executable name(s)
EXE = dict1 dict2 dict3

all: $(EXE)

$(EXE): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LDLIBS) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXE)

IDIR =./include
CC=g++ -std=c++17
CFLAGS=-I$(IDIR) -lSDL2main -lSDL2

ODIR=obj
LDIR =./lib

SRCR =./src

_DEPS = graphics.hpp game.hpp input.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = graphics.o game.o input.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SRCR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm program

run:
	./program
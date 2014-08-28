export CXX=c++
export CFLAGS= -I/usr/local/include -Wall -ansi -pedantic -Os
export LDFLAGS= -L/usr/local/lib -lGL -lSDL2 -lSDL2_image -lGLEW
EXEC=projet-freebsd
SRC= main.cpp
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ) util/util.o loader/loader.o graphic/graphic.o engine/engine.o
	$(CXX) -o $@ $^ $(LDFLAGS)
%.o:	%.cpp
	$(CXX) -o $@ -c $< $(CFLAGS)
util/util.o:
	gmake -C util
loader/loader.o:
	gmake -C loader
graphic/graphic.o:
	gmake -C graphic
engine/engine.o:
	gmake -C engine
.PHONY: clean mrpropre depend

clean:
	rm -rf *.o
	gmake -C loader clean
	gmake -C util clean
	gmake -C graphic clean
	gmake -C engine clean
mrpropre: clean
	rm -rf $(EXEC)
depend:
	gmake depend -C util
	gmake depend -C loader
	gmake depend -C graphic
	gmake depend -C engine


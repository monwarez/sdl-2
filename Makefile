export CC=c++
export CFLAGS= -I/usr/local/include -Wall -g
export LDFLAGS= -L/usr/local/lib -lGL -lSDL2 -lSDL2_image -lGLEW -lassimp
EXEC=projet-freebsd
SRC= main.cpp
#SRC= main.cpp Game.cpp Shader.cpp DebugGL.cpp Error.cpp Graphics.cpp Input.cpp Window.cpp Scene.cpp Object.cpp Texture.cpp Camera.cpp MD2Loader.cpp FrameBuffer.cpp AssimpLoad.cpp
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

$(EXEC): $(OBJ) util/util.o loader/loader.o graphic/graphic.o engine/engine.o
	$(CC) -o $@ $^ $(LDFLAGS)
%.o:	%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
util/util.o:
	gmake -C util
loader/loader.o:
	gmake -C loader
graphic/graphic.o:
	gmake -C graphic
engine/engine.o:
	gmake -C engine
.PHONY: clean mrpropre

clean:
	rm -rf *.o
	gmake -C loader clean
	gmake -C util clean
	gmake -C graphic clean
	gmake -C engine clean
mrpropre: clean
	rm -rf $(EXEC)



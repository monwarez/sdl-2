export CC=c++
export CFLAGS= -I/usr/local/include -Wall -g
export LDFLAGS= -L/usr/local/lib -lGL -lSDL2 -lSDL2_image -lGLEW -lassimp
EXEC=projet
SRC= main.cpp Game.cpp Shader.cpp DebugGL.cpp Error.cpp Graphics.cpp Input.cpp Window.cpp Scene.cpp Object.cpp Texture.cpp Camera.cpp MD2Loader.cpp FrameBuffer.cpp AssimpLoad.cpp
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

projet: $(OBJ) util/util.o loader/loader.o
	$(CC) -o $@ $^ $(LDFLAGS)
%.o:	%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
util/util.o:
	gmake -C util
loader/loader.o:
	gmake -C loader
.PHONY: clean mrpropre

clean:
	rm -rf *.o
	gmake -C loader clean
mrpropre: clean
	rm -rf $(EXEC)



CC=c++
CFLAGS= -I/usr/local/include -Wall -g
LDFLAGS= -L/usr/local/lib -lGL -lSDL2 -lSDL2_image -lGLEW
EXEC=projet
SRC= main.cpp Game.cpp Shader.cpp DebugGL.cpp Error.cpp Graphics.cpp Input.cpp Window.cpp Scene.cpp Object.cpp Texture.cpp Camera.cpp MD2Loader.cpp FrameBuffer.cpp
OBJ= $(SRC:.cpp=.o)

all: $(EXEC)

projet: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)
%.o:	%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)
.PHONY: clean mrpropre

clean:
	rm -rf *.o
mrpropre: clean
	rm -rf $(EXEC)



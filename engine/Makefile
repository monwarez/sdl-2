OBJ=engine.o
all:	$(OBJ)

engine.o:	Camera.o FrameBuffer.o Game.o Object.o Scene.o RcManager.o
	ld -o $@ -Ur $^
%.o: %.cpp
	$(CC) -c $^ $(CFLAGS)
clean:
	rm -f $(OBJ) *.o



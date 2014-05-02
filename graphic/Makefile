OBJ= graphic.o
all:	$(OBJ)

graphic.o:	Graphics.o Texture.o Window.o
	ld -o $@ -Ur $^
%.o: %.cpp
	$(CC) -c $^ $(CFLAGS)
clean:
	rm -f $(OBJ) *.o



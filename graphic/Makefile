OBJ= graphic.o
all:	$(OBJ)

graphic.o:	Graphics.o Texture.o Window.o
	ld -o $@ -Ur $^
%.o: %.cpp
	$(CXX) -c $^ $(CFLAGS)
clean:
	rm -f $(OBJ) *.o
depend:
	$(CXX) -E -MM *.cpp $(CFLAGS) > .depend



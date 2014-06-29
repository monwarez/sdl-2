OBJ=engine.o
all:	$(OBJ)

engine.o:	Camera.o FrameBuffer.o Game.o Object.o Scene.o RcManager.o Light.o
	ld -o $@ -Ur $^
%.o: %.cpp
	$(CXX) -c $^ $(CFLAGS)
clean:
	rm -f $(OBJ) *.o

depend:
	$(CXX) -E -MM *.cpp $(CFLAGS) > .depend

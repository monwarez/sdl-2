OBJ=util.o
all:	$(OBJ)

util.o:	Parser.o Error.o DebugGL.o Input.o Shader.o
	ld -o $@ -Ur $^
%.o: %.cpp
	$(CXX) -c $^ $(CFLAGS)
clean:
	rm -f $(OBJ) *.o



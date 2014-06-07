OBJ=loader.o
all:	$(OBJ)

loader.o:	AbstractLoader.o MD2Loader.o
	ld -o $@ -Ur $^
%.o: %.cpp
	$(CXX) -c $^ $(CFLAGS)
clean:
	rm -f $(OBJ) *.o



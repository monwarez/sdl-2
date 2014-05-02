OBJ=util.o
all:	$(OBJ)

util.o:	Parser.o
	ld -o $@ -Ur $^
%.o: %.cpp
	$(CC) -c $^ $(CFLAGS)
clean:
	rm -f $(OBJ) *.o



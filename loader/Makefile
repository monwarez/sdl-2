OBJ=loader.o
all:	$(OBJ)

loader.o:	AbstractLoader.o
	cp AbstractLoader.o loader.o
%.o: %.cpp
	$(CC) -c $^ 
clean:
	rm -f $(OBJ) *.o



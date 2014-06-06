example:
	$(CC) -Wfatal-errors -g -O0 -o example src/rand/*.c src/rand/mt/*.c src/rand/mrg/*.c src/*.c

static:
	$(CC) -fPIC -O0 -o src/*.c && ar rcs libngram.a src/*.o


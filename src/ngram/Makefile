test:
	$(CC) -Wfatal-errors -g -O0 -o ngram src/*.c

static:
	$(CC) -fPIC -O0 -o src/*.c && ar rcs libngram.a src/*.o


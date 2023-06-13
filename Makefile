CC=gcc
FILES=src/main.c src/lib/utils.c src/lib/algorithm.c

all: debug

debug: $(FILES)
	if [ ! -d bin ]; then mkdir bin; fi
	$(CC) -g $^ -o bin/main 

run: debug
	./bin/main

release: $(FILES)
	if [ ! -d bin ]; then mkdir bin; fi
	$(CC) $^ -o bin/main -O3

python: $(FILES)
	if [ ! -d bin ]; then mkdir bin; fi
	$(CC) -fPIC -shared -o bin/bus.so $^ -O3

clean:
	rm -f bin/*

baseline: src/baseline.c
	if [ ! -d bin ]; then mkdir bin; fi
	$(CC) -g $^ -o bin/baseline

test: debug baseline
	diff --color=always -y -w -B --suppress-common-lines <(./bin/baseline) <(./bin/main)

all:
	mkdir bin/
	gcc src/main.c src/node_config.c src/haversin.c -o bin/mobility_analyser -Wall -static -std=gnu99 -lm -O2

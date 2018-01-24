default: run
folder:
	mkdir -p build
build: folder
	gcc -lncurses -o build/cnake src/linkedlist.c src/libcnake.c src/cnake.c
debug:
	gcc -lncurses -g src/linkedlist.c src/libcnake.c src/cnake.c

run: build
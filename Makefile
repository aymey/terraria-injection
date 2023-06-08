COMPILER = gcc

all: *
	export LD_LIBRARY_PATH=./injector

	cd injector && make && cd ..
	$(COMPILER) -I./injector/ -L./injector -linjector main.c -o output

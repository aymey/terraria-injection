COMPILER = gcc
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:./injector

all: *
	cd injector && make && cd ..
	$(COMPILER) -I./injector/ -L./injector -linjector -Wl,-rpath,'$$ORIGIN/injector' main.c -o output

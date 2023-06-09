COMPILER = gcc
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:./injector
# echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope

all: *
	cd injector && make && cd ..
	$(COMPILER) -I./injector/ -L./injector -linjector -Wl,-rpath,'$$ORIGIN/injector' main.c -shared -fPIC -o output.so
	$(COMPILER) -I./injector/ -L./injector -linjector -Wl,-rpath,'$$ORIGIN/injector' inject.c -o output

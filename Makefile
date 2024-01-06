gcc_args=-ggdb
main:
	gcc $(gcc_args) -o main main.c 
dump: main
	objdump -d main > main.dump
clean:
	rm -f main
	rm -f main.dump
.PHONY: clean main

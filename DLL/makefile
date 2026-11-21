CC = gcc
CFLAGS = -Iinclude -std=c2x -Wall -Wextra -pedantic -g -fsanitize=address,undefined

all: build/final
run: all
	./build/final

build/final: build/main.o build/dll.o
	@echo "Link final"
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: src/%.c
	@mkdir -p build
	@echo "Compile $< -> $@"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "Removing all builds"
	rm -rf build


.PHONY: all clean run
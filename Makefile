CC = gcc
CFLAGS = -Wall -Wextra -O2
OUT = output

all: ascii_to_decimal factorial string_binary_to_decimal binary_operations singleton_linked_list

ascii_to_decimal:
				mkdir -p build
				$(CC) $(CFLAGS) samples/ascii_to_decimal/src.c -o build/ascii_to_decimal

factorial:
				mkdir -p build
				$(CC) $(CFLAGS) samples/factorial/src.c -o build/factorial

string_binary_to_decimal:
				mkdir -p build
				$(CC) $(CFLAGS) samples/string_binary_to_decimal/src.c -o build/string_binary_to_decimal

binary_operations:
				mkdir -p build
				$(CC) $(CFLAGS) samples/binary_operations/src.c -o build/binary_operations

singleton_linked_list:
				mkdir -p build
				$(CC) $(CFLAGS) samples/singleton_linked_list/src.c -o build/singleton_linked_list

clean:
	rm -rf build
CC = gcc
CFLAGS = -Wall -Wextra -O2
OUT = output

all: ascii_to_decimal factorial string_binary_to_decimal

ascii_to_decimal:
				mkdir -p build
				$(CC) $(CFLAGS) samples/ascii_to_decimal/src.c -o build/ascii_to_decimal

factorial:
				mkdir -p build
				$(CC) $(CFLAGS) samples/factorial/src.c -o build/factorial

string_binary_to_decimal:
				mkdir -p build
				$(CC) $(CFLAGS) samples/string_binary_to_decimal/src.c -o build/string_binary_to_decimal

clean:
	rm -rf build
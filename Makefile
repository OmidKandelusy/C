CC = gcc
CFLAGS = -Wall -Wextra -O2
OUT = output

all: ascii_to_decimal factorial string_binary_to_decimal binary_operations singleton_linked_list simple_hashtable_search doubly_linked_list binary_search_tree graph_traversal

ascii_to_decimal:
				mkdir -p build
				$(CC) $(CFLAGS) fundamental_examples/ascii_to_decimal/src.c -o build/ascii_to_decimal

factorial:
				mkdir -p build
				$(CC) $(CFLAGS) fundamental_examples/factorial/src.c -o build/factorial

string_binary_to_decimal:
				mkdir -p build
				$(CC) $(CFLAGS) fundamental_examples/string_binary_to_decimal/src.c -o build/string_binary_to_decimal

binary_operations:
				mkdir -p build
				$(CC) $(CFLAGS) fundamental_examples/binary_operations/src.c -o build/binary_operations

singleton_linked_list:
				mkdir -p build
				$(CC) $(CFLAGS) fundamental_examples/singleton_linked_list/src.c -o build/singleton_linked_list

simple_hashtable_search:
				mkdir -p build
				$(CC) $(CFLAGS) fundamental_examples/simple_hashtable_search/src.c -o build/simple_hashtable_search

doubly_linked_list:
				mkdir -p build
				$(CC) $(CFLAGS) fundamental_examples/doubly_linked_list/src.c -o build/doubly_linked_list

binary_search_tree:
				mkdir -p build
				$(CC) $(CFLAGS) fundamental_examples/binary_search_tree/src.c -o build/binary_search_tree

graph_traversal:
				mkdir -p build
				$(CC) $(CFLAGS) fundamental_examples/graph_traversal/src.c -o build/graph_traversal

clean:
	rm -rf build
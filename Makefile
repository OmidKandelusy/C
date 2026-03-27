CC = gcc
CFLAGS = -Wall -Wextra -O2
OUT = output

all: ascii_to_decimal basic_math string_binary_to_decimal bitwise_operations singleton_linked_list simple_hashtable_search doubly_linked_list binary_search_tree graph_traversal


# this section belongs to essentials directory content

basic_math:
				mkdir -p build
				$(CC) $(CFLAGS) essentials/basic_math/src.c -o build/basic_math

bitwise_operations:
				mkdir -p build
				$(CC) $(CFLAGS) essentials/bitwise_operations/src.c -o build/bitwise_operations

singleton_linked_list:
				mkdir -p build
				$(CC) $(CFLAGS) essentials/singleton_linked_list/src.c -o build/singleton_linked_list

simple_hashtable_search:
				mkdir -p build
				$(CC) $(CFLAGS) essentials/simple_hashtable_search/src.c -o build/simple_hashtable_search

doubly_linked_list:
				mkdir -p build
				$(CC) $(CFLAGS) essentials/doubly_linked_list/src.c -o build/doubly_linked_list

binary_search_tree:
				mkdir -p build
				$(CC) $(CFLAGS) essentials/binary_search_tree/src.c -o build/binary_search_tree

graph_traversal:
				mkdir -p build
				$(CC) $(CFLAGS) essentials/graph_traversal/src.c -o build/graph_traversal

# this section belongs to problems directory content

string_binary_to_decimal:
				mkdir -p build
				$(CC) $(CFLAGS) problems/string_binary_to_decimal/src.c -o build/string_binary_to_decimal

ascii_to_decimal:
				mkdir -p build
				$(CC) $(CFLAGS) problems/ascii_to_decimal/src.c -o build/ascii_to_decimal

clean:
	rm -rf build
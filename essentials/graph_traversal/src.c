/** standard C header files */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ====================================================================
// global definitions and macros

#define GRAPH_MAX_SIZE 20

uint8_t graph[GRAPH_MAX_SIZE][GRAPH_MAX_SIZE];

// ====================================================================
// helper functions

void graph_init(void) { memset(graph, 0, sizeof(graph)); }

void add_an_edge(void) {
  int err = -1;
  int first_node_of_edge = -1;
  int second_node_of_edge = -1;

  printf("insert the starting node of the edge (the node's index starting from "
         "0) \n\r");
  err = scanf("%d", &first_node_of_edge);
  if (err != 1) {
    printf("[Error], invalid user input for the node index \n\r");
    return;
  }

  if (first_node_of_edge < 0 || first_node_of_edge >= GRAPH_MAX_SIZE) {
    printf("[Error], node index is out of range \n\r");
    printf("         try something between 0 and %d\n\r", GRAPH_MAX_SIZE);
    return;
  }

  printf("insert the ending node of the edge (the node's index starting from "
         "0) \n\r");
  err = scanf("%d", &second_node_of_edge);
  if (err != 1) {
    printf("[Error], invalid user input for the node index \n\r");
    return;
  }

  graph[first_node_of_edge][second_node_of_edge] = 1;
  graph[second_node_of_edge][first_node_of_edge] = 1;

  return;
}

void display_graph(void) {
  printf("the graph in a matrix format \n\n\r");

  for (int i = 0; i < GRAPH_MAX_SIZE; i++) {
    for (int j = 0; j < GRAPH_MAX_SIZE; j++) {
      printf("%d ", graph[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

void load_preset_graph(void) {
  /** This function populates the graph with the
      following preset pattern

               (0)
              /   \
            (1)   (2)
           /      /  \
         (3)    (4)  (5)
         / \
       (6) (7)

  */
  graph[0][1] = 1;
  graph[1][0] = 1;

  graph[0][2] = 1;
  graph[2][0] = 1;

  graph[1][3] = 1;
  graph[3][1] = 1;

  graph[2][4] = 1;
  graph[4][2] = 1;

  graph[2][5] = 1;
  graph[5][2] = 1;

  graph[3][6] = 1;
  graph[6][3] = 1;

  graph[3][7] = 1;
  graph[7][3] = 1;

  return;
}

void remove_an_edge(void) {
  int err = -1;
  int first_node_of_edge = -1;
  int second_node_of_edge = -1;

  printf("insert the starting node of the edge (the node's index starting from "
         "0) \n\r");
  err = scanf("%d", &first_node_of_edge);
  if (err != 1) {
    printf("[Error], invalid user input for the node index \n\r");
    return;
  }

  if (first_node_of_edge < 0 || first_node_of_edge >= GRAPH_MAX_SIZE) {
    printf("[Error], node index is out of range \n\r");
    printf("         try something between 0 and %d\n\r", GRAPH_MAX_SIZE);
    return;
  }

  printf("insert the ending node of the edge (the node's index starting from "
         "0) \n\r");
  err = scanf("%d", &second_node_of_edge);
  if (err != 1) {
    printf("[Error], invalid user input for the node index \n\r");
    return;
  }

  graph[first_node_of_edge][second_node_of_edge] = 0;
  graph[second_node_of_edge][first_node_of_edge] = 0;

  return;
}

int if_visited(uint8_t *visted_list, uint8_t list_len, uint8_t node_index) {
  if (!visted_list) {
    printf("[Error, null pointer encountered \n\r]");
    return -1;
  }
  if (node_index < 0 || node_index > 255) {
    printf("[Error], invalid node_index input \n\r");
    return -2;
  }
  for (int i = 0; i < list_len; i++) {
    uint8_t check = *(uint8_t *)(visted_list + i);
    if (check == node_index) {
      return 1;
    }
  }

  return 0;
}

void traversal_bfs(void) {

  int err = 0;
  uint8_t start_node = 0;
  printf("from what node you want to start the BFS search ? \n\r");
  err = scanf("%hhu", &start_node);
  if (err != 1) {
    printf("[Error], invalid input for the start_node \n\r");
    return;
  }

  if (start_node >= GRAPH_MAX_SIZE) {
    printf("[Error], start_node is too big \n\r");
    return;
  }

  uint8_t dequeue_index = 0;
  uint8_t enqueue_index = 0;

  uint8_t visited[GRAPH_MAX_SIZE] = {0};      // record traversal order
  uint8_t search_queue[GRAPH_MAX_SIZE] = {0}; // BFS queue

  // enqueue start node
  search_queue[enqueue_index++] = start_node;
  visited[0] = start_node;

  while (dequeue_index < enqueue_index) {
    uint8_t current = search_queue[dequeue_index++]; // dequeue

    // explore neighbors
    for (int i = 0; i < GRAPH_MAX_SIZE; i++) {
      // connected and not visited
      if (graph[current][i] == 1 &&
          if_visited(visited, enqueue_index, i) == 0) {
        search_queue[enqueue_index] = i; // enqueue
        visited[enqueue_index++] = i;    // mark visited in order
      }
    }
  }

  // print traversal
  printf("\n BFS traversal: \n\r");
  for (int i = 0; i < enqueue_index; i++) {
    printf("%d -> ", visited[i]);
  }
  printf("END\n\n");
}

int search_unvisited_neighbor(uint8_t node, uint8_t *visited,
                              uint8_t visited_len) {
  for (int i = 0; i < GRAPH_MAX_SIZE; i++) {
    if (graph[node][i] == 1 && if_visited(visited, visited_len, i) == 0) {
      return i;
    }
  }
  return -1;
}

void dfs_recursive(uint8_t node, uint8_t *visited, uint8_t *count) {
  visited[*count] = node;
  (*count)++;

  while (1) {
    int next = search_unvisited_neighbor(node, visited, *count);

    if (next == -1) {
      return; // backtrack
    }

    dfs_recursive((uint8_t)next, visited, count);
  }
}

void traversal_dfs(void) {

  int err = 0;

  uint8_t start_node = 0;
  printf("from what node you want to start the DFS search ? \n\r");
  err = scanf("%hhu", &start_node);
  if (err != 1) {
    printf("[Error], invalid input for the start_node \n\r");
    return;
  }

  if (start_node >= GRAPH_MAX_SIZE) {
    printf("[Error], start_node is too big \n\r");
    return;
  }

  uint8_t visited[GRAPH_MAX_SIZE] = {0};
  uint8_t count = 0;

  dfs_recursive(start_node, visited, &count);

  printf("\n DFS traversal: \n\r");
  for (int i = 0; i < count; i++) {
    printf("%d -> ", visited[i]);
  }
  printf("END\n");
}
// ====================================================================
// example's main interactive routine

int main(void) {

  // intitialize the graph structure:
  graph_init();

  printf("This example illustrates the BFS and DFS graph traversal techniques "
         "\n\r");

  bool exit_flag = false;
  int user_choice = -1;
  int err = 0;

  while (!exit_flag) {
    printf("select your choice \n\r");
    printf("1. add one edge to the graph\n\r");
    printf("2. load the preset graph \n\r");
    printf("3. display the graph \n\r");
    printf("4. remove an edge from the graph \n\r");
    printf("5. Do the BFS traversal \n\r");
    printf("6. Do the DFS traversal \n\r");
    printf("7. exit \n\r");

    err = scanf("%d", &user_choice);
    if (err != 1) {
      printf("[Error], invalid input \n\r");
      return 0;
    }

    switch (user_choice) {
    case 7:
      return 0;

    case 1:
      add_an_edge();
      break;

    case 2:
      load_preset_graph();
      break;

    case 3:
      display_graph();
      break;

    case 4:
      remove_an_edge();
      break;

    case 5:
      traversal_bfs();
      break;

    case 6:
      traversal_dfs();
      break;

    default:
      printf("unrecognized menu index \n\r");
      break;
    }
  }

  return 0;
}

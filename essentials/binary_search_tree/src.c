/** standard C header files */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===============================================================
// type defintions and global variables

typedef struct node_s {
  int label;
  int data;
  struct node_s *left;
  struct node_s *right;
} node_t;

node_t *root = NULL;

// ================================================================
// helper functions

int create_node(node_t **new_node) {
  if (!new_node) {
    return -1;
  }

  node_t *node = malloc(sizeof(node_t));
  if (!node) {
    return -2;
  }

  // node feilds instantiation:
  node->label = -1;
  node->data = -1;
  node->left = NULL;
  node->right = NULL;

  *new_node = node;

  return 0;
}

int insert_node(int label, int data) {

  int err = 0;

  if (!root) {
    err = create_node(&root);
    if (err < 0) {
      return err;
    }

    root->label = label;
    root->data = data;

    return err;
  }

  node_t *new_node = NULL;
  err = create_node(&new_node);
  if (err < 0) {
    return err;
  }

  node_t *current = root;

  while (1) {

    if (current->label > label) {
      if (current->left == NULL) {
        current->left = new_node;
        new_node->label = label;
        new_node->data = data;
        break;
      }

      current = current->left;

    } else if (current->label < label) {
      if (current->right == NULL) {
        current->right = new_node;
        new_node->label = label;
        new_node->data = data;
        break;
      }

      current = current->right;

    } else {
      free(new_node);
      return -3;
    }
  }

  return err;
}

int find_node_and_its_parent(int label, node_t **node, node_t **parent) {
  if (!root) {
    return -1;
  }

  node_t *current = root;
  node_t *parent_node = NULL;

  while (current != NULL && current->label != label) {

    if (current->label > label) {
      parent_node = current;
      current = current->left;
    } else {
      parent_node = current;
      current = current->right;
    }
  }

  if (!current) {
    return -2;
  }

  if (node) {
    *node = current;
  }
  if (parent) {
    *parent = parent_node;
  }

  return 0;
}

int remove_leaf(node_t *node, node_t *parent) {
  if (!node) {
    return -1;
  }

  if (!parent) {
    // this is a root node
    free(node);
    root = NULL;
    return 0;
  }

  if (parent->left == node) {
    parent->left = NULL;
  } else {
    parent->right = NULL;
  }

  free(node);
  return 0;
}

int remove_one_child_node(node_t *node, node_t *parent) {
  if (!node) {
    return -1;
  }

  node_t *child = node->left ? node->left : node->right;

  if (!parent) {
    // this is a root
    root = child;
  } else if (parent->left == node) {
    parent->left = child;
  } else if (parent->right == node) {
    parent->right = child;
  } else {
    return -2;
  }

  free(node);

  return 0;
}

int remove_two_children_node(node_t *node, node_t *parent) {
  if (!node) {
    return -1;
  }

  // search for the smallest label in the right branch:
  // (this node can keep the BST pattern sound after replacement)
  node_t *replacement = node->right;
  node_t *replacement_parent = node;
  while (replacement->left) {
    replacement_parent = replacement;
    replacement = replacement->left;
  }

  // updating the node:
  node->label = replacement->label;
  node->data = replacement->data;

  // if the replacement has a child, it must be a right child!
  // if the replacement is a leaf, no child transfer nedded!
  if (replacement_parent->left == replacement) {
    replacement_parent->left = replacement->right;
  } else {
    replacement_parent->right = replacement->right;
  }

  // done with the replacement into node, free the replacement variable:
  free(replacement);

  return 0;
}

int remove_node(int label) {

  node_t *node = NULL;
  node_t *parent = NULL;
  int err = find_node_and_its_parent(label, &node, &parent);
  if (err < 0) {
    return err;
  }

  uint8_t children_count = 0;
  if (node->left) {
    children_count++;
  }
  if (node->right) {
    children_count++;
  }

  switch (children_count) {
  case 0:
    remove_leaf(node, parent);
    break;

  case 1:
    remove_one_child_node(node, parent);
    break;

  case 2:
    remove_two_children_node(node, parent);
    break;

  default:
    break;
  }

  return 0;
};

// ===============================================================================
// example interaction functions:

void add_user_node(void) {
  int user_label = -1;
  int user_data = -1;
  printf("enter the node label (integer) \n\r");
  scanf("%d", &user_label);
  printf("enter the node data (integer) \n\r");
  scanf("%d", &user_data);

  int err = insert_node(user_label, user_data);
  if (err) {
    printf("[Error], adding failed, err:%d\n\r", err);
  }

  return;
}

void list_nodes_recursive(node_t *node) {
  if (!node) {
    return;
  }

  // first left:
  list_nodes_recursive(node->left);
  printf("-- node, label:%d, data:%d \n\r", node->label, node->data);

  list_nodes_recursive(node->right);

  return;
}

void list_all_nodes(void) {
  node_t *current_node = root;
  if (!current_node) {
    printf("The tree is empty, first add nodes ... \n\r");
    return;
  }

  printf("\n tree nodes are (searching `in-order`) \n\r");
  list_nodes_recursive(root);

  printf("\n");

  return;
}

void request_node_removal(void) {

  // first list all the nodes
  list_all_nodes();

  printf("\n select the node label to remove\n\r");
  int user_choice = -1;
  scanf("%d", &user_choice);

  int err = remove_node(user_choice);
  if (err < 0) {
    printf("[Error], removing the node failed, err:%d\n\r", err);
    return;
  }

  printf("node labeled %d got removed \n\r", user_choice);

  return;
}

int main(void) {

  printf("this examples illustrates binary search tree (BST) logic \n\r");
  printf("choose from the menu\n\r");

  bool exit_flag = false;
  int user_choice = -1;

  while (!exit_flag) {
    printf("1. Add a node \n\r");
    printf("2. List all nodes \n\r");
    printf("3. Remove a node \n\r");
    printf("4. Exit\n\r");

    scanf("%d", &user_choice);

    switch (user_choice) {
    case 1:
      add_user_node();
      break;

    case 2:
      list_all_nodes();
      break;

    case 3:
      request_node_removal();
      break;

    case 4:
      exit_flag = true;
      break;

    default:
      break;
    }
  }

  return 0;
}
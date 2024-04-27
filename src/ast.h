#ifndef AST_H
#define AST_H

// Node class which represents a node in a tree
class Node {
public:
  Node(std::string);
  //~Node();
  // Print representation of the node
  std::string p_key;
  // Left and right child of the node
  Node* left_child;
  Node* right_child;
  bool is_leaf();
};

// Binary tree
class BT {
public:
  // Root of our tree
  Node* root;
  BT(Node*);
  //~BT();
};

void print_post_order(BT);

// AST definition to represent a boolean expression
class AST : public BT {
public:
  AST(Node* root);
};

AST build_ast_prefix(std::string);

#endif

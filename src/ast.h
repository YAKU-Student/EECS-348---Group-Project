#ifndef AST_H
#define AST_H

#include <string>

// Node class which represents a node in a tree
class Node {
   public:
    Node(std::string);
    // Print representation of the node
    std::string p_key;
    // Left and right child of the node
    Node* left_child;
    Node* right_child;
    bool is_leaf();
    virtual bool evaluate() { return true; };
    virtual ~Node() = default;
};

// Binary tree
class BT {
   public:
    // Root of our tree
    Node* root;
    BT();
    ~BT();
    void print_post_order();
};

// AST definition to represent a boolean expression
class AST : public BT {
   public:
    AST();
    void build_ast_prefix(std::string);
    bool evaluate();
};

#endif

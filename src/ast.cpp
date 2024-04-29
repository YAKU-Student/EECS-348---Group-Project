/*---------------------------------------------------------------------
Basic Abstract Syntax Tree (AST) for boolean expressions.
Author: YAKU-Student

Our AST is a binary tree with the operation as a parent node and each
child as either a leaf or a subtree. Each subtree represents a valid
boolean subexpression. Each leaf represents a boolean. Each
subexpression is evaluated bottom up which ensures no abiguity between
order of operation.

We define generic nodes and binary trees and then specialize to create
our AST.
---------------------------------------------------------------------*/
#include "ast.h"

#include <cstring>
#include <iostream>
#include <string>

/* Generic Node and Tree Definitions*/

// Node is initialized to be a leaf
Node::Node(std::string p_key) {
    this->p_key = p_key;
    this->left_child = nullptr;
    this->right_child = nullptr;
}

// Returns true if the node is a leaf
bool Node::is_leaf() { return ((this->left_child == nullptr) && (this->right_child == nullptr)); }

// Set root of a BT
BT::BT() { this->root = nullptr; }

// Recursly destroy children then parent
void _rec_destroy(Node* node) {
    if (!(node->is_leaf())) {
        if (node->left_child != nullptr) {
            _rec_destroy(node->left_child);
        }

        if (node->right_child != nullptr) {
            _rec_destroy(node->right_child);
        }
    }

    delete node;
}

// Destroy root
BT::~BT() {
    _rec_destroy(this->root);
    this->root = nullptr;
}

void _rec_print_post_order(Node* node) {
    // Print node if it is a leaf
    if (node->is_leaf()) {
        std::cout << (std::string)node->p_key;
        return;
    }

    // Print left and right child and then key of the current node
    if (node->left_child != nullptr) {
        _rec_print_post_order(node->left_child);
    }

    if (node->right_child != nullptr) {
        _rec_print_post_order(node->right_child);
    }

    std::cout << (std::string)node->p_key;
}

// Print the tree in post order
void BT::print_post_order() { _rec_print_post_order(this->root); }

/* AST Nodes Specification */

// Operation node - represents an operation
// Note: In final tree, this node must have a left and right child and
// key must match the operation
enum Operation { AND, OR, NAND, XOR };

class OperationNode : public Node {
   public:
    OperationNode(std::string, Operation);
    Operation operation;
    bool evaluate();
};

OperationNode::OperationNode(std::string key, Operation operation) : Node::Node(key) { this->operation = operation; }

// Evaluate children and then evaluate with operation
bool OperationNode::evaluate() {
    bool lv = this->left_child->evaluate();
    bool rv = this->right_child->evaluate();

    switch (this->operation) {
        case AND:
            return lv && rv;
        case OR:
            return lv || rv;
        case NAND:
            return !(lv && rv);
        case XOR:
            return (!lv && rv) || (lv && !rv);
    }

    return true;
}

// Boolean node - represents a boolean value of true or false
// Note: In final tree, this node should be a leaf
class BooleanNode : public Node {
   public:
    BooleanNode(std::string, bool);
    bool value;
    bool evaluate();
};

BooleanNode::BooleanNode(std::string key, bool value) : Node::Node(key) { this->value = value; }

// Return value to evaluate
bool BooleanNode::evaluate() { return this->value; }

// Unary Node: Node which represents a unary operation
// Note: Operand should be the left child with right child be nullptr
enum UOperation { NOT };

class UnaryNode : public Node {
   public:
    UnaryNode(std::string, UOperation);
    UOperation operation;
    bool evaluate();
};

UnaryNode::UnaryNode(std::string key, UOperation operation) : Node::Node(key) { this->operation = operation; }

// Evaluate left child and return unary value
bool UnaryNode::evaluate() {
    bool lv = this->left_child->evaluate();

    switch (this->operation) {
        case NOT:
            return !lv;
    }

    return true;
}

AST::AST() : BT::BT(){};

// Make a boolean operation node based on key
OperationNode* _make_operation_node(std::string& key) {
    // Get operation based on key
    Operation operation;

    if (key == "&") {
        operation = AND;
    } else if (key == "|") {
        operation = OR;
    } else if (key == "@") {
        operation = NAND;
    } else if (key == "$") {
        operation = XOR;
    }

    return new OperationNode(key, operation);
}

// Make a boolean leaf node based on key
BooleanNode* _make_boolean_node(std::string& key) {
    // Get value based on key
    bool value;

    if (key == "T") {
        value = true;
    } else if (key == "F") {
        value = false;
    }

    return new BooleanNode(key, value);
}

// Make a unary node based on key
UnaryNode* _make_unary_node(std::string& key) {
    // Get unary operation based on key
    UOperation operation = NOT;

    return new UnaryNode(key, operation);
}

static int i = 0;

Node* _build_node_prefix(const std::string& expr) {
    std::string fst_char = expr.substr(i, 1);

    // If character is a boolean, then it is a leaf and return that node
    if ((fst_char == "T") || (fst_char == "F")) {
        i++;
        return _make_boolean_node(fst_char);
    }

    // If character is a unary, then make a unary node. Otherwise
    // operator node
    Node* node;
    bool is_unary;
    if (fst_char == "!") {
        node = _make_unary_node(fst_char);
        is_unary = true;
    } else {
        node = _make_operation_node(fst_char);
        is_unary = false;
    }

    i++;

    // Attach both left and right nodes
    Node* left_node = _build_node_prefix(expr);
    Node* right_node = nullptr;

    if (!(is_unary)) {
        right_node = _build_node_prefix(expr);
    }

    node->left_child = left_node;
    node->right_child = right_node;
    return node;
}

// Make a new tree from a boolean expression in prefix notation
// Eg. !((!T)|F)&((T@F)$(!T)) in infix is
//     !&|!TF$@TF!T in prefix
void AST::build_ast_prefix(const std::string& expr) {
    i = 0;
    Node* root = _build_node_prefix(expr);
    this->root = root;
}

// Evaluate AST node
bool AST::evaluate() { return this->root->evaluate(); }

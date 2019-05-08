#include <stdlib.h>
#include <string.h>


struct node_binary_tree {
    void *value;
    struct binary_tree *tree;
    struct node_binary_tree *left, *right, *father;
    int size_tree;
};

struct binary_tree {
    struct node_binary_tree *root;
    int (*comparison) (const void *p1, const void *p2);
    char *type;
    size_t size_type;
};


typedef struct node_binary_tree node_binary_tree;
typedef struct binary_tree binary_tree;


void __init__NodeBinaryTree(node_binary_tree *node) {
    node = (node_binary_tree *) malloc(sizeof(node_binary_tree));
    node->tree = NULL;
    node->value = NULL;
    node->left = node->right = node->father = NULL;
    node->size_tree = 0;
}


void __setFather__NodeBinaryTree(node_binary_tree *current, node_binary_tree *father) {
    current->father = father;
}


void __setTree__NodeBinaryTree(node_binary_tree *node, binary_tree *tree) {
    node->tree = tree;
}


void __setValue__NodeBinaryTree(node_binary_tree *node, const void *value, size_t size) {
    node->value = malloc(size);
    memcpy(node->value, value, size);
}


void __set__NodeBinaryTree(node_binary_tree *node, binary_tree *tree, node_binary_tree *father) {
    __init__NodeBinaryTree(node);
    __setFather__NodeBinaryTree(node, father);
    __setTree__NodeBinaryTree(node, tree);
}


void insert_node_binary_tree(node_binary_tree *current, const void *new_value) {
    current->size_tree++;

    if(!current->value) {
        __setValue__NodeBinaryTree(current, new_value, current->tree->size_type);
        __set__NodeBinaryTree(current->left, current->tree, current);
        __set__NodeBinaryTree(current->right, current->tree, current);
        return;
    }


    if(current->tree->comparison(current->value, new_value) < 0)
        insert_node_binary_tree(current->left, new_value);
    else
        insert_node_binary_tree(current->right, new_value);
}


void __init__BinaryTree(binary_tree *tree) {
    tree = (binary_tree *) malloc(sizeof(binary_tree));
    tree->type = NULL;
    tree->comparison = NULL;
    tree->root = NULL;
    tree->size_type = 0;
}


void __setComparison__BinaryTree(binary_tree *tree, int (*comparison) (const void *p1, const void *p2)) {
    tree->comparison = comparison;
}


void __setType__BinaryTree(binary_tree *tree, char *type, size_t size_type) {
    tree->type = (char *) malloc( sizeof(char) * (strlen(type) + 1) );
    
    strcpy(tree->type, type);
    tree->size_type = size_type;
}


void __set__BinaryTree(binary_tree *tree, int (*comparison) (const void *p1, const void *p2),
    char *type, size_t size_type) {

    __init__BinaryTree(tree);
    __set__NodeBinaryTree(tree->root, tree, NULL);
    __setComparison__BinaryTree(tree, comparison);
    __setType__BinaryTree(tree, type, size_type);
}


void insert_value_binary_tree(binary_tree *tree, const void *value) {
    insert_node_binary_tree(tree->root, value);
}
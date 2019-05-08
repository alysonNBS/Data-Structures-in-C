#include <stdio.h>
#include "../Tree/Binary_tree/binary_tree.c"

int comp(const void *p1, const void *p2) {
    return *((int*)p1) < *((int*)p2);
}

int main() {
    int a = 10;
    binary_tree *tree;

    printf("0");

    __set__BinaryTree(tree, comp, "int", sizeof(int));

    printf("A");

    insert_value_binary_tree(tree, &a);

    printf("B");

    printf("%d %d", a, *((int*) tree->root->value));

    return 0;
}
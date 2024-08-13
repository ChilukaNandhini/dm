#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_ITEMS 100
#define MAX_TRANSACTIONS 100
typedef struct FPNode {
 int item;
 int count;
 struct FPNode *parent;
 struct FPNode *next;
 struct FPNode *children[MAX_ITEMS];
} FPNode;
typedef struct {
 int item;
 int count;
} ItemCount;
typedef struct {
 FPNode *head;
 FPNode *tail;
} HeaderTableEntry;
FPNode *create_node(int item, FPNode *parent) {
 FPNode *node = (FPNode *)malloc(sizeof(FPNode));
 node->item = item;
 node->count = 1;
 node->parent = parent;
 node->next = NULL;
 memset(node->children, 0, sizeof(node->children));
 return node;
}
void add_transaction(FPNode *root, int *transaction, int length, HeaderTableEntry
*header_table) {
 FPNode *current_node = root;
 for (int i = 0; i < length; i++) {
 int item = transaction[i];
 if (!current_node->children[item]) {
 FPNode *new_node = create_node(item, current_node);
 current_node->children[item] = new_node;
 if (header_table[item].head == NULL) {
 header_table[item].head = header_table[item].tail = new_node;
 } else {
 header_table[item].tail->next = new_node;
 header_table[item].tail = new_node;
 }
 } else {
 current_node->children[item]->count++;
 }
 current_node = current_node->children[item];
 }
}
void build_fptree(int transactions[MAX_TRANSACTIONS][MAX_ITEMS], int
num_transactions, int min_support, FPNode *root, HeaderTableEntry
*header_table) {
 for (int i = 0; i < MAX_ITEMS; i++) {
 header_table[i].head = header_table[i].tail = NULL;
 }
 for (int i = 0; i < num_transactions; i++) {
 int transaction[MAX_ITEMS];
 int length = 0;
 for (int j = 0; j < MAX_ITEMS && transactions[i][j] != -1; j++) {
 transaction[length++] = transactions[i][j];
 }
 add_transaction(root, transaction, length, header_table);
 }
}
void print_fptree(FPNode *node, int depth) {
 for (int i = 0; i < depth; i++) printf(" ");
 printf("%d:%d\n", node->item, node->count);
 for (int i = 0; i < MAX_ITEMS; i++) {
 if (node->children[i]) {
 print_fptree(node->children[i], depth + 1);
 }
 }
}
int main() {
 int transactions[MAX_TRANSACTIONS][MAX_ITEMS] = {
 {1, 2, 5, -1},
 {2, 4, -1},
 {2, 3, -1},
 {1, 2, 4, -1},
 {1, 3, -1},
 {2, 3, -1},
 {1, 3, -1},
 {1, 2, 3, 5, -1},
 {1, 2, 3, -1}
 };
 int num_transactions = 9;
 int min_support = 2;
 FPNode *root = create_node(-1, NULL);
 HeaderTableEntry header_table[MAX_ITEMS];
 build_fptree(transactions, num_transactions, min_support, root, header_table);
 printf("FP-Tree:\n");
 print_fptree(root, 0);
 return 0;
}







Output:

FP-Tree:
-1:1
 1:6
  2:4
   3:2
    5:1
   4:1
   5:1
  3:2
 2:3
  3:2
  4:1
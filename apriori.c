#include <stdio.h>
#include <stdlib.h>
#define MAX_ITEMS 100
#define MAX_ITEMSET_SIZE 10
#define MAX_TRANSACTIONS 100
typedef struct {
 int items[MAX_ITEMS];
 int count;
} Itemset;
typedef struct {
 Itemset itemsets[MAX_ITEMSET_SIZE];
 int count;
} ItemsetList;
typedef struct {
 int items[MAX_ITEMS];
 int count;
} Transaction;
Transaction transactions[MAX_TRANSACTIONS];
int num_transactions = 0;
int min_support = 2;
void read_transactions() {
 transactions[0].items[0] = 1;
 transactions[0].items[1] = 2;
 transactions[0].count = 2;
 transactions[1].items[0] = 2;
 transactions[1].items[1] = 3;
 transactions[1].count = 2;
 num_transactions = 2;
}
int is_subset(Itemset *subset, Itemset *set) {
 int i, j;
 for (i = 0; i < subset->count; i++) {
 int found = 0;
 for (j = 0; j < set->count; j++) {
 if (subset->items[i] == set->items[j]) {
 found = 1;
 break;
 }
 }
 if (!found) return 0;
 }
 return 1;
}
int count_support(Itemset *itemset) {
 int count = 0, i;
 for (i = 0; i < num_transactions; i++) {
 if (is_subset(itemset, &transactions[i])) {
 count++;
 }
 }
 return count;
}
void generate_candidates(ItemsetList *prev_itemsets, ItemsetList *candidates) {
 int i, j, k;
 candidates->count = 0;
 for (i = 0; i < prev_itemsets->count; i++) {
 for (j = i + 1; j < prev_itemsets->count; j++) {
 Itemset new_itemset;
 new_itemset.count = prev_itemsets->itemsets[i].count + 1;
 
 for (k = 0; k < prev_itemsets->itemsets[i].count; k++) {
 new_itemset.items[k] = prev_itemsets->itemsets[i].items[k];
 }
 new_itemset.items[new_itemset.count - 1] = prev_itemsets->itemsets[j].items[prev_itemsets->itemsets[j].count - 1];
 if (count_support(&new_itemset) >= min_support) {
 candidates->itemsets[candidates->count++] = new_itemset;
 }
 }
 }
}
void apriori() {
 ItemsetList current_itemsets, candidates;
 int i, k;
 // Initialize with single item itemsets
 current_itemsets.count = 0;
 for (i = 0; i < MAX_ITEMS; i++) {
 Itemset itemset;
 itemset.count = 1;
 itemset.items[0] = i;
 if (count_support(&itemset) >= min_support) {
 current_itemsets.itemsets[current_itemsets.count++] = itemset;
 }
 }
 k = 1;
 while (current_itemsets.count > 0) {
 printf("Frequent itemsets of size %d:\n", k);
 for (i = 0; i < current_itemsets.count; i++) {
 int j;
 for (j = 0; j < current_itemsets.itemsets[i].count; j++) {
 printf("%d ", current_itemsets.itemsets[i].items[j]);
 }
 printf("\n");
 }
 generate_candidates(&current_itemsets, &candidates);
 current_itemsets = candidates;
 k++;
 }
}
int main() {
 read_transactions();
 apriori();
 return 0;
}
 






Output:

Frequent itemsets of size 1:
2 
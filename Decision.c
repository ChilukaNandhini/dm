#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_FEATURES 10 // Adjust as needed
#define MAX_EXAMPLES 100 // Adjust as needed
typedef struct {
 double features[MAX_FEATURES];
 int label;
} Example;
typedef struct Node {
 int feature_index; // Index of the feature used for the split
 double threshold; // Threshold for the split
 struct Node *left; // Pointer to the left subtree
 struct Node *right; // Pointer to the right subtree
 int class_label; // Class label for leaf nodes
 int is_leaf; // Flag to determine if the node is a leaf
} Node;
//2. Calculate Gini Index
double gini_index(int *labels, int n) {
 int count[2] = {0, 0}; // Assuming binary classification (0 and 1)
 for (int i = 0; i < n; i++) {
 count[labels[i]]++;
 }
 double p0 = (double)count[0] / n;
 double p1 = (double)count[1] / n;
 return 1.0 - (p0 * p0 + p1 * p1);
}
void best_split(Example *data, int *labels, int n, int num_features, int *best_feature,
double *best_threshold, double *best_gini) {
 *best_gini = 1.0;
 *best_feature = -1;
 *best_threshold = 0.0;
 for (int feature = 0; feature < num_features; feature++) {
 // Sort the data by the current feature
 for (int i = 0; i < n - 1; i++) {
 for (int j = i + 1; j < n; j++) {
 if (data[i].features[feature] > data[j].features[feature]) {
 Example temp = data[i];
 data[i] = data[j];
 data[j] = temp;
 int temp_label = labels[i];
 labels[i] = labels[j];
 labels[j] = temp_label;
 }
 }
 }
 for (int i = 0; i < n - 1; i++) {
 if (data[i].features[feature] == data[i + 1].features[feature]) continue;
 double threshold = (data[i].features[feature] + data[i + 1].features[feature]) /
2.0;
 int left_labels[MAX_EXAMPLES], right_labels[MAX_EXAMPLES];
 int left_count = 0, right_count = 0;
 for (int j = 0; j < n; j++) {
 if (data[j].features[feature] <= threshold) {
 left_labels[left_count++] = labels[j];
 } else {
 right_labels[right_count++] = labels[j];
 }
 }
 double gini_left = gini_index(left_labels, left_count);
 double gini_right = gini_index(right_labels, right_count);
 double weighted_gini = (left_count * gini_left + right_count * gini_right) / n;
 if (weighted_gini < *best_gini) {
 *best_gini = weighted_gini;
 *best_feature = feature;
 *best_threshold = threshold;
 }
 }
 }
}
Node* build_tree(Example *data, int *labels, int n, int num_features, int max_depth,
int depth) {
 Node *node = (Node *)malloc(sizeof(Node));
 node->left = NULL;
 node->right = NULL;
 node->is_leaf = 0;
 int unique_labels[MAX_EXAMPLES];
 int label_count = 0;
 for (int i = 0; i < n; i++) {
 int already_present = 0;
 for (int j = 0; j < label_count; j++) {
 if (labels[i] == unique_labels[j]) {
 already_present = 1;
 break;
 }
 }
 if (!already_present) {
 unique_labels[label_count++] = labels[i];
 }
 }
 if (label_count == 1) {
 node->is_leaf = 1;
 node->class_label = labels[0];
 return node;
 }
 if (depth == max_depth) {
 node->is_leaf = 1;
 node->class_label = labels[0];
 return node;
 }
 int best_feature;
 double best_threshold;
 double best_gini;
 best_split(data, labels, n, num_features, &best_feature, &best_threshold,
&best_gini);
 if (best_feature == -1) {
 node->is_leaf = 1;
 node->class_label = labels[0];
 return node;
 }
 node->feature_index = best_feature;
 node->threshold = best_threshold;
 Example left_data[MAX_EXAMPLES];
 int left_labels[MAX_EXAMPLES];
 int left_count = 0;
 Example right_data[MAX_EXAMPLES];
 int right_labels[MAX_EXAMPLES];
 int right_count = 0;
 for (int i = 0; i < n; i++) {
 if (data[i].features[best_feature] <= best_threshold) {
 left_data[left_count] = data[i];
 left_labels[left_count++] = labels[i];
 } else {
 right_data[right_count] = data[i];
 right_labels[right_count++] = labels[i];
 }
 }
 node->left = build_tree(left_data, left_labels, left_count, num_features,
max_depth, depth + 1);
 node->right = build_tree(right_data, right_labels, right_count, num_features,
max_depth, depth + 1);
 return node;
}
int predict(Node *root, Example example) {
 if (root->is_leaf) {
 return root->class_label;
 }
 if (example.features[root->feature_index] <= root->threshold) {
 return predict(root->left, example);
 } else {
 return predict(root->right, example);
 }
}
int main() {
 // Example data and labels
 Example data[MAX_EXAMPLES] = {
 {{2.5, 1.5}, 0},
 {{3.5, 2.5}, 1},
 {{1.5, 1.0}, 0},
 {{2.0, 2.0}, 1},
 // Add more examples as needed
 };
 int labels[] = {0, 1, 0, 1}; // Corresponding labels
 int num_examples = 4;
 int num_features = 2;
 int max_depth = 2;
 Node *root = build_tree(data, labels, num_examples, num_features, max_depth,
0);
 // Predict a new example
 Example new_example = {{2.0, 1.5}};
 int prediction = predict(root, new_example);
 printf("Prediction: %d\n", prediction);
 return 0;
}
 





Output:

Prediction: 0
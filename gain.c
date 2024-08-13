#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_FEATURES 10 
#define MAX_EXAMPLES 100 
typedef struct {
    double features[MAX_FEATURES];
    int label;
} Example;
typedef struct {
    double threshold;
    int feature_index;
} Split;
double entropy(int *labels, int n);
double information_gain(Example *data, int *labels, int n, int feature_index, double threshold);
void find_best_split(Example *data, int *labels, int n, int num_features, Split *best_split, double *best_gain);
double entropy(int *labels, int n) {
    int count[2] = {0, 0}; // Assuming binary classification (0 and 1)
    for (int i = 0; i < n; i++) {
        count[labels[i]]++;
    }
    double p0 = (double)count[0] / n;
    double p1 = (double)count[1] / n;
    double e0 = p0 > 0 ? -p0 * log2(p0) : 0;
    double e1 = p1 > 0 ? -p1 * log2(p1) : 0;
    return e0 + e1;
}
double information_gain(Example *data, int *labels, int n, int feature_index, double threshold) {
    int left_labels[MAX_EXAMPLES], right_labels[MAX_EXAMPLES];
    int left_count = 0, right_count = 0;
    for (int i = 0; i < n; i++) {
        if (data[i].features[feature_index] <= threshold) {
            left_labels[left_count++] = labels[i];
        } else {
            right_labels[right_count++] = labels[i];
        }
    }
    double entropy_before = entropy(labels, n);
    double entropy_left = entropy(left_labels, left_count);
    double entropy_right = entropy(right_labels, right_count);
    double weighted_entropy_after = (left_count * entropy_left + right_count * entropy_right) / n;
    return entropy_before - weighted_entropy_after;
}
void find_best_split(Example *data, int *labels, int n, int num_features, Split *best_split, double *best_gain) {
    *best_gain = 0.0;
    best_split->feature_index = -1;
    best_split->threshold = 0.0;
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
            double threshold = (data[i].features[feature] + data[i + 1].features[feature]) / 2.0;
            double gain = information_gain(data, labels, n, feature, threshold);
            if (gain > *best_gain) {
                *best_gain = gain;
                best_split->feature_index = feature;
                best_split->threshold = threshold;
            }
        }
    }
}
int main() {
    Example data[MAX_EXAMPLES] = {
        {{2.5, 1.5}, 0},
        {{3.5, 2.5}, 1},
        {{1.5, 1.0}, 0},
        {{2.0, 2.0}, 1},
    };
    int labels[] = {0, 1, 0, 1}; // Corresponding labels
    int num_examples = 4;
    int num_features = 2;
    Split best_split;
    double best_gain;
    find_best_split(data, labels, num_examples, num_features, &best_split, &best_gain);
    printf("Best feature index: %d\n", best_split.feature_index);
    printf("Best threshold: %f\n", best_split.threshold);
    printf("Best information gain: %f\n", best_gain);
    return 0;
}




Output:

Best feature index: 1
Best threshold: 1.750000
Best information gain: 1.000000
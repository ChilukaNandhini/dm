#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int feature1;
    int feature2;
    int label; 
} DataInstance;
void train(DataInstance *data, int numInstances, double *priorProbabilities, double **conditionalProbabilities) {
    int classCounts[2] = {0}; 
    int featureCounts[2][2] = {0}; 
    for (int i = 0; i < numInstances; ++i) {
        int label = data[i].label;
        classCounts[label]++;
        featureCounts[label][data[i].feature1]++;
        featureCounts[label][data[i].feature2]++;
    }
    for (int c = 0; c < 2; ++c) {
        priorProbabilities[c] = (double)classCounts[c] / numInstances;
    }
    for (int c = 0; c < 2; ++c) {
        for (int f = 0; f < 2; ++f) {
            conditionalProbabilities[c][f] = (double)(featureCounts[c][f] + 1) / (classCounts[c] + 2); 
        }
    }
}
int classify(int feature1, int feature2, double *priorProbabilities, double **conditionalProbabilities) {
    double posteriorProbabilities[2];
    for (int c = 0; c < 2; ++c) {
        posteriorProbabilities[c] = priorProbabilities[c] * conditionalProbabilities[c][feature1] * conditionalProbabilities[c][feature2];
    }
    return (posteriorProbabilities[0] > posteriorProbabilities[1]) ? 0 : 1;
}

int main() {
    DataInstance data[] = {
        {1, 0, 0}, // Example instance 1: feature1=1, feature2=0, label=0
        {0, 1, 1}, // Example instance 2: feature1=0, feature2=1, label=1
    };
    int numInstances = sizeof(data) / sizeof(data[0]);
    double priorProbabilities[2];
    double *conditionalProbabilities[2];
    for (int i = 0; i < 2; ++i) {
        conditionalProbabilities[i] = (double *)malloc(2 * sizeof(double));
    }
    train(data, numInstances, priorProbabilities, conditionalProbabilities);
    int newFeature1 = 1;
    int newFeature2 = 0;
    int predictedClass = classify(newFeature1, newFeature2, priorProbabilities, conditionalProbabilities);
    printf("Predicted class for (feature1=%d, feature2=%d): %d\n", newFeature1, newFeature2, predictedClass);
    for (int i = 0; i < 2; ++i) {
        free(conditionalProbabilities[i]);
    }
    return 0;
}




Output:

Predicted class for (feature1=1, feature2=0): 1
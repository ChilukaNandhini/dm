#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define NUM_POINTS 10 
#define K 2 
#define MAX_ITER 100
typedef struct {
 double x;
 double y;
} Point;
typedef struct {
 double x;
 double y;
} Centroid;
double euclideanDistance(Point p1, Centroid c);
int assignCluster(Point point, Centroid centroids[]);
void updateCentroids(Point points[], int clusterAssgn[], Centroid centroids[]);
void printClusters(Point points[], int clusterAssgn[]);
int main() {
 Point points[NUM_POINTS];
 Centroid centroids[K];
 int clusterAssignment[NUM_POINTS];
 srand(time(NULL));
 for (int i = 0; i < NUM_POINTS; ++i) {
 points[i].x = (double)(rand() % 100);
 points[i].y = (double)(rand() % 100);
 }
 for (int i = 0; i < K; ++i) {
 centroids[i].x = (double)(rand() % 100);
 centroids[i].y = (double)(rand() % 100);
 }
 int iter = 0;
 while (iter < 2) {
 for (int i = 0; i < NUM_POINTS; ++i) {
 clusterAssignment[i] = assignCluster(points[i], centroids);
 }
 updateCentroids(points, clusterAssignment, centroids);
 printf("Iteration %d:\n", iter + 1);
 printClusters(points, clusterAssignment);
 iter++;
 }
 return 0;
}
double euclideanDistance(Point p, Centroid c) {
 return sqrt(pow(p.x - c.x, 2) + pow(p.y - c.y, 2));
}
int assignCluster(Point point, Centroid centroids[]) {
 double minDist = euclideanDistance(point, centroids[0]);
 int cluster = 0;
 for (int i = 1; i < K; ++i) {
 double dist = euclideanDistance(point, centroids[i]);
 if (dist < minDist) {
 minDist = dist;
 cluster = i;
 }
 }
 return cluster;
}
void updateCentroids(Point points[], int clusterAssgn[], Centroid centroids[]) {
 int counts[K] = {0};
 double sumX[K] = {0};
 double sumY[K] = {0};
 for (int i = 0; i < NUM_POINTS; ++i) {
 int cluster = clusterAssgn[i];
 sumX[cluster] += points[i].x;
 sumY[cluster] += points[i].y;
 counts[cluster]++;
 }
 for (int i = 0; i < K; ++i) {
 centroids[i].x = sumX[i] / counts[i];
 centroids[i].y = sumY[i] / counts[i];
 }
}
void printClusters(Point points[], int clusterAssgn[]) {
 for (int k = 0; k < K; ++k) {
 printf("Cluster %d:\n", k + 1);
 for (int i = 0; i < NUM_POINTS; ++i) {
 if (clusterAssgn[i] == k) {
 printf("(%.2f, %.2f) ", points[i].x, points[i].y);
 }
 }
 printf("\n");
 }
 printf("\n");
}
 



Output:

Iteration 1:
Cluster 1:
(37.00, 71.00) (54.00, 88.00) (33.00, 51.00) (71.00, 96.00) 
Cluster 2:
(88.00, 11.00) (63.00, 10.00) (80.00, 34.00) (14.00, 38.00) (11.00, 45.00) (51.00, 28.00) 

Iteration 2:
Cluster 1:
(37.00, 71.00) (54.00, 88.00) (71.00, 96.00) 
Cluster 2:
(88.00, 11.00) (63.00, 10.00) (80.00, 34.00) (14.00, 38.00) (11.00, 45.00) (33.00, 51.00) (51.00, 28.00) 
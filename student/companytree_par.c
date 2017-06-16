#include "companytree.h"
#define T 8 //threshold

void parallelTranverse(tree *node, int n){
    if(node != NULL){
        node->work_hours = compute_workHours(node->data);
        top_work_hours[node->id] = node->work_hours;

#pragma omp task firstprivate(n) final(n<T)
        parallelTranverse(node->right, n-1);
#pragma omp task firstprivate(n) final(n<T)
        parallelTranverse(node->left, n-1);
    }
}

void traverse(tree *node, int numThreads){
#pragma omp parallel num_threads(numThreads)
    {
#pragma omp single
        parallelTranverse(node,numThreads);
    }
}


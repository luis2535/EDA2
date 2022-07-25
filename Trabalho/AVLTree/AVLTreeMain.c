#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "AVLTree.h"

void printSteps(FILE *filePointer){
    fprintf(filePointer, "%i ", countSteps);
    countSteps = 0;    
}

void worstCase(){
    tree *AVL;
    AVL = createTree();
    FILE *filePointer;
    filePointer = fopen("PerformanceWorstCase.txt", "w+");
    for(int i = 0; i < 1000; i++){
        addNode(AVL, i);
        printSteps(filePointer);
    }
}

void averageCase(int n){
    tree *AVL;
    FILE *filePointer;
    filePointer = fopen("PerformanceAverageCase.txt", "w+");
    srand(time(NULL));

    for(int i = 0; i < n; i++){
        AVL = createTree();
        for(int j = 0; j < 1000; j++){
            addNode(AVL, rand());
            printSteps(filePointer);
        }
        if(i != n-1) fprintf(filePointer, "\n");
        free(AVL);
        AVL = NULL;
    }
}

int main(){
    worstCase();
    averageCase(10);
}
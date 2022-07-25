#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "BTree.h"
#define ORDEM 5

void printSteps(FILE *filePointer){
    fprintf(filePointer, "%i ", contador);
    contador = 0;    
}

void WorstCase(){
    FILE *filePointer;
    filePointer = fopen("PerformanceWorstCase.txt", "w+");
    ArvoreB *B;
    B = criaArvore(ORDEM);

    for(int i = 0; i < 1000; i++){
        adicionaChave(B, i);   
        printSteps(filePointer);
        
    }
    fprintf(filePointer, "\n");
    free(B);
}

void AverageCase(int n){
    FILE *filePointer;
    filePointer = fopen("PerformanceAverageCase.txt", "w+");
    ArvoreB *B;
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        B = criaArvore(ORDEM);
        for(int j = 0; j < 1000; j++){
            
            adicionaChave(B, rand());
            printSteps(filePointer);    
        }
    
        if(i != n-1) fprintf(filePointer, "\n");
        free(B);
        B = NULL;
    }
}

int main(){
    WorstCase();
    AverageCase(10);
}
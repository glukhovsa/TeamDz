#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(type, array, x, y) type z=array[x]; array[x]=array[y]; array[y]=z;

void generation(int *array1, int *array2, int len){
    int i, g;
    for(i=0; i<len; i++){
        g=rand()%201;
        array1[i]=g;
        array2[i]=g;
    }
}

int check(int *array1, int *array2, int size){
    for(int i=0; i<size; i++)
        if(array1[i]!=array2[i])
            return 0;
    return 1;
}

int bubbleSort(int *array, int size){
    time_t start = time(NULL);
    for(int i=0; i<size-1; i++)
        for(int j=size-1; j>i; j--)
            if(array[j-1]>array[j]){
                SWAP(int, array, j-1, j);
            }
    return time(NULL)-start;
}

void heapSort(int *array, int size){
}

int main(){
    FILE *file;
    file=fopen("file.txt", "w");
    int length, timeBubble, timeHeap;
    for(length=30000; length<=60000; length+=200){
        int *massBubble=malloc(sizeof(int)*length);
        int *massHeap=malloc(sizeof(int)*length);
        generation(massBubble, massHeap, length);
        timeBubble=bubbleSort(massBubble, length);
        timeHeap=0;
        if(!(check(massBubble, massBubble, length))){
            printf("The functions are not working properly %d", length);
            break;
        }else
            fprintf(file, "%d %d %d\n", length, timeBubble, timeHeap);
        free(massBubble);
        free(massHeap);
    }
    fclose(file);
    WinExec("Graph.py", 0);
}

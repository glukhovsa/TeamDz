#include <stdio.h>
#include <stdlib.h>

void generation(int *array, int len){
    for(int i=0; i<len; i++)
        array[i]=rand()%201;
}

void bubbleSort(int *array, int size){
    for(int i=0; i<size-1; i++)
        for(int j=size-1; j>i; j--)
            if(array[j-1]>array[j]){
                int swap=array[j-1];
                array[j-1]=array[j];
                array[j]=swap;
            }
}

int main(){
    int len=4, i;
    char c;
    int *array=array=malloc(sizeof(int)*len);;
    generation(array, len);
    for(i=0; i<len; i++)
        printf("%d ", array[i]);
    bubbleSort(array, len);
    printf("\n");
    for(i=0; i<len; i++)
        printf("%d ", array[i]);
}

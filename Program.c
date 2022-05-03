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

  void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
  }

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
  
    if (left < n && arr[left] > arr[largest])
      largest = left;
  
    if (right < n && arr[right] > arr[largest])
      largest = right;
  
    if (largest != i) {
      swap(&arr[i], &arr[largest]);
      heapify(arr, n, largest);
    }
  }

  int heapSort(int arr[], int n) {
    time_t start = time(NULL);
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
      swap(&arr[0], &arr[i]);
      heapify(arr, i, 0);
    }
    return time(NULL)-start;
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

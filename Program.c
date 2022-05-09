
`#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(type, array, x, y) type z=array[x]; array[x]=array[y]; array[y]=z; //������, �������� ������� �������� �������
#define MIN_SIZE 5000;
#define MAX_SIZE 35000;
#define STEP 50;

void generation(int *array1, int *array2, int len){ //�������, ����������� ��� ���������� �������, ����������, �� ����������� �������
    int i, g;
    for(i=0; i<len; i++){
        g=rand()%201;
        array1[i]=g;
        array2[i]=g;
    }
}

float bubbleSort(int *array, int size){ //������� ���������� ���������, ��������� ��������� �� ������, � ���������� ����� ������ ���������
    int start = clock(); //���������� ���������� start(������ ���������� ����� ��������� � ������ ������� ���������)
    for(int i=size-1; i>0; i--)
        for(int j=0; j<i; j++) //����� �� ������� �� ������� �������� �� i ��������
            if(array[j-1]>array[j])
                SWAP(int, array, j-1, j); //"���������" ������� � �������� ������� �������� "�����"
    return ((clock()-start)*1.0)/CLOCKS_PER_SEC; //���������� ������� ����� ����������� �����, ��������� � ������ ���������, � ��������� ���������� start, �������� �������� � �������
}

void heapify(int *arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
      largest = left;

    if (right < n && arr[right] > arr[largest])
      largest = right;

    if (largest != i) {
      SWAP(int, arr, i, largest);
      heapify(arr, n, largest);
    }
}

float heapSort(int *arr, int n) {
    int start = clock();
    for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);
    for (int i = n - 1; i >= 0; i--) {
      SWAP(int, arr, 0, i);
      heapify(arr, i, 0);
    }
    return ((clock()-start)*1.0)/CLOCKS_PER_SEC;
  }

int main(){
    FILE *file;
    file=fopen("file.txt", "w"); //�������� ����� ��� ������ � ����
    int length;
    float timeBubble, timeHeap;
    for(length=MIN_SIZE; length<=MAX_SIZE; length+=STEP){ //�������������� ������ ���������� ��� �������� ������ �� MIN_SIZE �� MAX_SIZE
        int *massBubble=malloc(sizeof(int)*length); //��������� ������ ��� ������, ������� ����� ������������ ����������� ���������
        int *massHeap=malloc(sizeof(int)*length); //��������� ������ ��� ������, ������� ����� ������������ ������������� �����������
        generation(massBubble, massHeap, length);
        timeBubble=bubbleSort(massBubble, length); //���������� ������� ���������, � ���������� timeBubble ��������� ����� ������ ���������
        timeHeap=heapSort(massHeap, length); //������������� ���������� �������, � ���������� timeBubble ��������� ����� ������ ���������
        fprintf(file, "%d %f %f\n", length, timeBubble, timeHeap); //������ ���������� ������ � ����
        printf("%d\n", length);
        free(massBubble); //������������� ���������� ��� ������� ������
        free(massHeap); //������������� ���������� ��� ������� ������
    }
    fclose(file); //�������� �����
}

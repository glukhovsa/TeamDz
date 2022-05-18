#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_SIZE 2000
#define MAX_SIZE 10000
#define STEP 25

void generation(int *array1, int *array2, int len){ //�������, ����������� ��� ���������� �������, ����������, �� ����������� �������
    int i, g;
    for(i=0; i<len; i++){
        g=rand()%201;
        array1[i]=g;
        array2[i]=g;
    }
}

void SWAP(int *array, int x, int y){
    int z=array[x];
    array[x]=array[y];
    array[y]=z;
}

void bubbleSort(int *array, int size){ //������� ���������� ���������, ��������� ��������� �� ������, � ���������� ����� ������ ���������
    for(int i=0; i<size-1; i++)
        for(int j=size-1; j>i; j--) //����� �� ������� �� ������� �������� �� i ��������
            if(array[j-1]>array[j])
                SWAP(array, j-1, j); //"���������" ������� � �������� ������� �������� "�����"
}


void heapify(int *arr, int n, int i) {
    int largest = i;    //������� ������
    int left = 2 * i + 1; //������� ������ � ������� ������� ����� �����
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) // ���������� �������� ������� � ����� ��������
      largest = left;                         // ���� �������� ������ ���������, ����������� ������ ��������� ��� ����������

    if (right < n && arr[right] > arr[largest]) // ���������� �������� ������� � ������� ��������
      largest = right;                          // ���� �������� ������ ���������, ����������� ������ ��������� ��� ����������

    if (largest != i) {                         //���� ������ ���������, ����� ������ ��������, �������� ����������� ��������
      SWAP(arr, i, largest);
      heapify(arr, n, largest);                 //� ��� ��� �������� ��� ������� ��� ���������
    }
}

float heapSort(int *arr, int n) {
    for (int i = n / 2 - 1; i >= 0; i--)   // ������� �������� ������, ��� ������� �������� ������� - ������������, � ������ �������� ������ ������ ���������.
      heapify(arr, n, i);                  // n/2-1 -��� ��� �������� �������� � ������.
    for (int i = n - 1; i >= 0; i--) {
      SWAP(arr, 0, i);         //�� ���������� ��������� ������ ���������� � �����, ����� ������� �������� ������� �� ��������� �����, �� ����
                                    //����� ������������ ������� � ����� �������, ����� �������� ������������� ��������� ������,
                                    //����� ����� ������������ ������� �� ����� �������� �����, ��� �� ������� ��������� �������,
                                    //� ����� ����� ������ ��� ������������� ������� � ��������, � ��� ���� �� ��������� �� ����� �������
      heapify(arr, i, 0);
    }
  }

int main(){
    FILE *file;
    file=fopen("file.txt", "w"); //�������� ����� ��� ������ � ����
    int length, start;
    float timeBubble, timeHeap;
    for(length=MIN_SIZE; length<=MAX_SIZE; length+=STEP){ //�������������� ������ ���������� ��� �������� ������ �� MIN_SIZE �� MAX_SIZE
        int *massBubble=malloc(sizeof(int)*length); //��������� ������ ��� ������, ������� ����� ������������ ����������� ���������
        int *massHeap=malloc(sizeof(int)*length); //��������� ������ ��� ������, ������� ����� ������������ ������������� �����������
        generation(massBubble, massHeap, length);

        start=clock();
        bubbleSort(massBubble, length); //���������� ������� ���������, � ���������� timeBubble ��������� ����� ������ ���������
        timeBubble=(clock()-start)*1.0/CLOCKS_PER_SEC;

        start=clock();
        heapSort(massHeap, length); //������������� ���������� �������, � ���������� timeBubble ��������� ����� ������ ���������
        timeHeap=(clock()-start)*1.0/CLOCKS_PER_SEC;

        generation(massBubble, massHeap, length);

        start=clock();
        bubbleSort(massBubble, length); //���������� ������� ���������, � ���������� timeBubble ��������� ����� ������ ���������
        timeBubble=timeBubble+(clock()-start)*1.0/CLOCKS_PER_SEC;

        start=clock();
        heapSort(massHeap, length); //������������� ���������� �������, � ���������� timeBubble ��������� ����� ������ ���������
        timeHeap=timeHeap+(clock()-start)*1.0/CLOCKS_PER_SEC;

        generation(massBubble, massHeap, length);

        start=clock();
        bubbleSort(massBubble, length);
        timeBubble=(timeBubble+(clock()-start)*1.0/CLOCKS_PER_SEC)/3;

        start=clock();
        heapSort(massHeap, length);
        timeHeap=(timeHeap+(clock()-start)*1.0/CLOCKS_PER_SEC)/3;

        fprintf(file, "%d %f %f\n", length, timeBubble, timeHeap); //������ ���������� ������ � ����
        free(massBubble); //������������� ���������� ��� ������� ������
        free(massHeap); //������������� ���������� ��� ������� ������
    }
    fclose(file); //�������� �����
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(type, array, x, y) type z=array[x]; array[x]=array[y]; array[y]=z; //макрос, меняющий местами элементы массива
#define MIN_SIZE 5000;
#define MAX_SIZE 35000;
#define STEP 50;

void generation(int *array1, int *array2, int len){ //функция, заполняющая два переданных массива, рандомными, но одинаковыми числами
    int i, g;
    for(i=0; i<len; i++){
        g=rand()%201;
        array1[i]=g;
        array2[i]=g;
    }
}

float bubbleSort(int *array, int size){ //функция сортировки пузырьком, принимает указатель на массив, а возвращает время работы алгоритма
    int start = clock(); //объявление переменной start(хранит количество тиков прошедших с начала запуска программы)
    for(int i=size-1; i>0; i--)
        for(int j=0; j<i; j++) //бежим по массиву от первого элемента до i элемента
            if(array[j-1]>array[j])
                SWAP(int, array, j-1, j); //"поднимаем" элемент с наиболее большим значение "вверх"
    return ((clock()-start)*1.0)/CLOCKS_PER_SEC; //возвращаем разницу между количеством тиков, прошедших с начала программы, и значением переменной start, переводя значение в секунды
}

void heapify(int *arr, int n, int i) {
    int largest = i;    //находим корень 
    int left = 2 * i + 1; //находим левого и правого ребенка этого корня
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) // сравниваем корневой элемент и левый дочерний
      largest = left;                         // если дочерний больше корневого, присваиваем индекс дочернего как наибольший

    if (right < n && arr[right] > arr[largest]) // сравниваем корневой элемент и правывй дочерний
      largest = right;                          // если дочерний больше корневого, присваиваем индекс дочернего как наибольший

    if (largest != i) {                         //если индекс поменялся, тогда меняем элементы, дочерний ставновится корневым
      SWAP(int, arr, i, largest);
      heapify(arr, n, largest);                 //и еще раз вызываем эту функцию для поддерева
    }
}

float heapSort(int *arr, int n) {
    int start = clock();                // засекаем начальное время старта сортировки
    for (int i = n / 2 - 1; i >= 0; i--)   // создаем бинарное дерево, где главный корневой элемент - макисмальный, а каждый дочерний меньше своего корневого.
      heapify(arr, n, i);                  // n/2-1 -это все корневые элементы в дереве.
    for (int i = n - 1; i >= 0; i--) {
      SWAP(int, arr, 0, i);         //по созданному бинарному дереву проходимся с конца, меняя главный корневой элемент на последнее место, то есть 
                                    //ставя максимальный элемент в конец массива, затем проводим реорганизацию бинарного дерева, 
                                    //снова ствая максимальный элемент на место главного корня, уже не учитвая последний элемент,
                                    //и затем снова меняем уже предпоследний элемент с корневым, и так пока не пройдемся по всему массиву
      heapify(arr, i, 0);
    }
    return ((clock()-start)*1.0)/CLOCKS_PER_SEC; // закничиваем измерение времени нашей сортировки
  }

int main(){
    FILE *file;
    file=fopen("file.txt", "w"); //открытие файла для записи в него
    int length;
    float timeBubble, timeHeap;
    for(length=MIN_SIZE; length<=MAX_SIZE; length+=STEP){ //рассматривание работу алгоритмов для массивов длиной от MIN_SIZE до MAX_SIZE
        int *massBubble=malloc(sizeof(int)*length); //выделение памяти под массив, который будет отсортирован сортировкой пузырьком
        int *massHeap=malloc(sizeof(int)*length); //выделение памяти под массив, который будет отсортирован пиромидальной сортировкой
        generation(massBubble, massHeap, length);
        timeBubble=bubbleSort(massBubble, length); //сортировка массива пузырьком, в переменную timeBubble заносится время работы алгоритма
        timeHeap=heapSort(massHeap, length); //пиромидальная сортировка массива, в переменную timeBubble заносится время работы алгоритма
        fprintf(file, "%d %f %f\n", length, timeBubble, timeHeap); //запись полученных данных в файл
        printf("%d\n", length);
        free(massBubble); //высвобождение выделенной для массива памяти
        free(massHeap); //высвобождение выделенной для массива памяти
    }
    fclose(file); //закрытие файла
}
}

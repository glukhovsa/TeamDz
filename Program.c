
`#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SWAP(type, array, x, y) type z=array[x]; array[x]=array[y]; array[y]=z; //ìàêðîñ, ìåíÿþùèé ìåñòàìè ýëåìåíòû ìàññèâà
#define MIN_SIZE 5000;
#define MAX_SIZE 35000;
#define STEP 50;

void generation(int *array1, int *array2, int len){ //ôóíêöèÿ, çàïîëíÿþùàÿ äâà ïåðåäàííûõ ìàññèâà, ðàíäîìíûìè, íî îäèíàêîâûìè ÷èñëàìè
    int i, g;
    for(i=0; i<len; i++){
        g=rand()%201;
        array1[i]=g;
        array2[i]=g;
    }
}

float bubbleSort(int *array, int size){ //ôóíêöèÿ ñîðòèðîâêè ïóçûðüêîì, ïðèíèìàåò óêàçàòåëü íà ìàññèâ, à âîçâðàùàåò âðåìÿ ðàáîòû àëãîðèòìà
    int start = clock(); //îáúÿâëåíèå ïåðåìåííîé start(õðàíèò êîëè÷åñòâî òèêîâ ïðîøåäøèõ ñ íà÷àëà çàïóñêà ïðîãðàììû)
    for(int i=size-1; i>0; i--)
        for(int j=0; j<i; j++) //áåæèì ïî ìàññèâó îò ïåðâîãî ýëåìåíòà äî i ýëåìåíòà
            if(array[j-1]>array[j])
                SWAP(int, array, j-1, j); //"ïîäíèìàåì" ýëåìåíò ñ íàèáîëåå áîëüøèì çíà÷åíèå "ââåðõ"
    return ((clock()-start)*1.0)/CLOCKS_PER_SEC; //âîçâðàùàåì ðàçíèöó ìåæäó êîëè÷åñòâîì òèêîâ, ïðîøåäøèõ ñ íà÷àëà ïðîãðàììû, è çíà÷åíèåì ïåðåìåííîé start, ïåðåâîäÿ çíà÷åíèå â ñåêóíäû
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
    file=fopen("file.txt", "w"); //îòêðûòèå ôàéëà äëÿ çàïèñè â íåãî
    int length;
    float timeBubble, timeHeap;
    for(length=MIN_SIZE; length<=MAX_SIZE; length+=STEP){ //ðàññìàòðèâàíèå ðàáîòó àëãîðèòìîâ äëÿ ìàññèâîâ äëèíîé îò MIN_SIZE äî MAX_SIZE
        int *massBubble=malloc(sizeof(int)*length); //âûäåëåíèå ïàìÿòè ïîä ìàññèâ, êîòîðûé áóäåò îòñîðòèðîâàí ñîðòèðîâêîé ïóçûðüêîì
        int *massHeap=malloc(sizeof(int)*length); //âûäåëåíèå ïàìÿòè ïîä ìàññèâ, êîòîðûé áóäåò îòñîðòèðîâàí ïèðîìèäàëüíîé ñîðòèðîâêîé
        generation(massBubble, massHeap, length);
        timeBubble=bubbleSort(massBubble, length); //ñîðòèðîâêà ìàññèâà ïóçûðüêîì, â ïåðåìåííóþ timeBubble çàíîñèòñÿ âðåìÿ ðàáîòû àëãîðèòìà
        timeHeap=heapSort(massHeap, length); //ïèðîìèäàëüíàÿ ñîðòèðîâêà ìàññèâà, â ïåðåìåííóþ timeBubble çàíîñèòñÿ âðåìÿ ðàáîòû àëãîðèòìà
        fprintf(file, "%d %f %f\n", length, timeBubble, timeHeap); //çàïèñü ïîëó÷åííûõ äàííûõ â ôàéë
        printf("%d\n", length);
        free(massBubble); //âûñâîáîæäåíèå âûäåëåííîé äëÿ ìàññèâà ïàìÿòè
        free(massHeap); //âûñâîáîæäåíèå âûäåëåííîé äëÿ ìàññèâà ïàìÿòè
    }
    fclose(file); //çàêðûòèå ôàéëà
}

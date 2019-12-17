
#define _CRT_SECURE_NO_WARNINGS

#pragma warning(disable : 4996)

#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#define MAX_SIZE 100000

#define MAX_QUE_SIZE 100




#define BUCKETS 10

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )




typedef struct {

   int heap[MAX_SIZE];

   int heap_size;

}HeapType;




typedef int element;

typedef struct {

   element data[MAX_QUE_SIZE];

   int front, rear;

}QueueType;







int* sorted[MAX_SIZE];










double selection_sort(int* arraySort, int N)

{

   int i, j, least, temp;

   clock_t start, end;




   start = clock();

   for (i = 0; i < N - 1; i++)

   {

      least = i;

      for (j = i + 1; j < N; j++)

      {

         if (arraySort[j] < arraySort[least])

            least = j;

      }

      temp = arraySort[i];

      arraySort[i] = arraySort[least];

      arraySort[least] = temp;

   }

   end = clock();




   return (end - start) / (double)1000;

}

double insertion_sort(int* arraySort, int N)

{

   int i, j, key;

   clock_t start, end;




   start = clock();

   for (i = 0; i < N; i++)

   {

      key = arraySort[i];

      for (j = i - 1; j >= 0 && arraySort[j] > key; j--)

         arraySort[j + 1] = arraySort[j];

      arraySort[j + 1] = key;

   }

   end = clock();




   return (end - start) / (double)1000;

}

double bubble_sort(int* arraySort, int N)

{

   int i, j, temp;

   clock_t start, end;




   start = clock();




   for (i = N - 1; i > 0; i--)

   {

      for (j = 0; j < i; j++)

      {

         if (arraySort[j] > arraySort[j + 1])

         {

            temp = arraySort[j];

            arraySort[j] = arraySort[j + 1];

            arraySort[j + 1] = temp;

         }

      }

   }




   end = clock();

   return (end - start) / (double)1000;

}

void inc_insertion_sort(int* arraySort, int first, int last, int gap)

{

   int i, j, key;

   for (i = first + gap; i <= last; i = i + gap)

   {

      key = arraySort[i];

      for (j = i - gap; j >= first && key < arraySort[j]; j = j - gap)

         arraySort[j + gap] = arraySort[j];

      arraySort[j + gap] = key;

   }

}




double shell_sort(int* arraySort, int N)

{

   int i, gap;

   clock_t start, end;




   start = clock();




   for (gap = N / 2; gap > 0; gap = gap / 2)

   {

      if (gap % 2 == 0) gap++;

      for (i = 0; i < gap; i++)

         inc_insertion_sort(arraySort, i, N - 1, gap);

   }




   end = clock();

   return (end - start) / (double)1000;

}

void initMerge(int size)

{

   int sorted = malloc(sizeof(int) * size);

}




void freeMerge()

{

   free(sorted);

}




// 합병정렬

void merge(int list[], int left, int mid, int right)

{

   int i, j, k, l;




   i = left; j = mid + 1; k = left;

   // 분할 정렬된 list의 합병

   while (i <= mid && j <= right) {

      if (list[i] <= list[j]) sorted[k++] = list[i++];

      else sorted[k++] = list[j++];

   }

   if (i > mid)    // 남아 있는 레코드의 일괄 복사

      for (l = j; l <= right; l++)

         sorted[k++] = list[l];

   else    // 남아 있는 레코드의 일괄 복사

      for (l = i; l <= mid; l++)

         sorted[k++] = list[l];

   // 배열 sorted[]의 리스트를 배열 list[]로 복사

   for (l = left; l <= right; l++)

      list[l] = sorted[l];

}




double merge_sort(int list[], int left, int right)

{

   int mid;

   clock_t start, end;




   start = clock();

   if (left < right)

   {

      mid = (left + right) / 2;              // 리스트의 균등분할

      merge_sort(list, left, mid);     // 부분리스트 정렬

      merge_sort(list, mid + 1, right);//부분리스트 정렬0

      merge(list, left, mid, right);    // 합병

   }




   end = clock();

   return (end - start) / (double)1000;

}

//퀵정렬

int partition(int list[], int left, int right)

{

   int pivot, temp;

   int low, high;




   low = left;

   high = right + 1;

   pivot = list[left];    //* 피벗 설정

   do {

      do

         low++;

      //* 왼쪽 리스트에서 피벗보다 큰 레코드 선택

      while (low <= right && list[low] < pivot);

      do

         high--;

      //* 오른쪽 리스트에서 피벗보다 작은 레코드 선택

      while (high >= left && list[high] > pivot);

      if (low < high) SWAP(list[low], list[high], temp);//* 선택된 두 레코드 교환

   } while (low < high);     //* 인덱스 i,j가 엇갈리지 않는 한 반복




   SWAP(list[left], list[high], temp); //* 인텍스 j가 가리키는 레코드와 피벗 교환\n

   printf("Swap[%d, %d]\n", list[left], list[high]);

   return high;

}

double quick_sort(int list[], int left, int right)

{

   clock_t start, end;




   start = clock();

   if (left < right) {    //* 리스트에 2개 이상의 레코드가 있을 경우

      int q = partition(list, left, right);

      quick_sort(list, left, q - 1);         //* 왼쪽 부분리스트를 퀵정렬

      quick_sort(list, q + 1, right);       //* 오른쪽 부분리스트를 퀵정렬

   }




   end = clock();

   return (end - start) / (double)1000;

}




int compare(const void* arg1, const void* arg2)

{

   if (*(int*)arg1 > * (int*)arg2) return 1;

   else if (*(int*)arg1 == *(int*)arg2) return 0;

   else return -1;

}




double quick_sort2(int list[], int size)

{

   clock_t start, end;

   start = clock();

   qsort((void*)list, (size_t)size, sizeof(int), compare);

   end = clock();

   return (end - start) / (double)1000;

}

// 생성 함수

HeapType* create()

{

   return (HeapType*)malloc(sizeof(HeapType));

}

// 초기화 함수

void init(HeapType* h)

{

   h->heap_size = 0;

}




// 현재 요소의 개수가 heap_size인 히프 h에 item을 삽입한다.

// 삽입 함수

void insert_max_heap(HeapType* h, int item)

{

   int i;

   i = ++(h->heap_size);




   //  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정

   while ((i != 1) && (item > h->heap[i / 2])) {

      h->heap[i] = h->heap[i / 2];

      i /= 2;

   }

   h->heap[i] = item;     // 새로운 노드를 삽입

}




// 삭제 함수

int delete_max_heap(HeapType* h)

{

   int parent, child;

   int item, temp;




   item = h->heap[1];

   temp = h->heap[(h->heap_size)--];

   parent = 1;

   child = 2;

   while (child <= h->heap_size) {

      // 현재 노드의 자식노드 중 더 작은 자식노드를 찾는다.

      if ((child < h->heap_size) &&

         (h->heap[child]) < h->heap[child + 1])

         child++;

      if (temp >= h->heap[child]) break;

      // 한 단계 아래로 이동

      h->heap[parent] = h->heap[child];

      parent = child;

      child *= 2;

   }

   h->heap[parent] = temp;

   return item;

}




double heap_sort(int list[], int n)

{

   int i;

   HeapType* h;

   clock_t start, end;




   start = clock();




   h = create();

   init(h);

   for (i = 0; i < n; i++) {

      insert_max_heap(h, list[i]);

   }

   for (i = (n - 1); i >= 0; i--) {

      list[i] = delete_max_heap(h);

   }

   free(h);

   end = clock();

   return (end - start) / (double)1000;

}




// 오류 함수

void error(char* message)

{

   fprintf(stderr, "%s\n", message);

   exit(1);

}

// 초기화 함수

void init2(QueueType* q)

{

   q->front = q->rear = 0;

}

// 공백 상태 검출 함수

int is_empty(QueueType* q)

{

   return (q->front == NULL);

}

// 포화 상태 검출 함수

int is_full(QueueType* q)

{

   return 0;

}

// 삽입 함수

void enqueue(QueueType* q, int item)

{

   if (is_full(q)) {

      error("큐가 포화상태입니다.");

      return;

   }

   q->data[++(q->rear)] = item;

}

// 삭제 함수

int dequeue(QueueType* q)

{

   if (is_empty(q)) {

      error("큐가 공백상태입니다.");

      return -1;

   }

   int item = q->data[++(q->front)];

   return item;

}










double radix_sort(int list[], int n, int digit)

{

   clock_t start, end;




   start = clock();

   int i, b, d, factor = 1;

   QueueType queues[BUCKETS];




   for (b = 0; b < BUCKETS; b++) init2(&queues[b]);  // 큐들의 초기화




   for (d = 0; d < digit; d++) {

      for (i = 0; i < n; i++)         // 데이터들을 자리수에 따라 큐에 삽입

         enqueue(&queues[(list[i] / factor) % 10], list[i]);




      for (b = i = 0; b < BUCKETS; b++)  // 버킷에서 꺼내어 list로 합친다.

         while (!is_empty(&queues[b]))

            list[i++] = dequeue(&queues[b]);

      factor *= 10;               // 그 다음 자리수로 간다.

   }

   end = clock();




   return (end - start) / (double)1000;

}




int getFileCount(char* fileName)

{

   FILE* pFile = fopen_s(&pFile, fileName, "r");

   int count = 0;

   char temp[10];

   char* a;




   if (pFile != NULL)

   {

      while (!feof(pFile))

      {

         a = fgets(temp, 10, pFile);

         count += 1;

      }

   }

   else

   {

      printf("< %s >파일이 존재하지 않습니다.\n", fileName);

      _getch();

      exit(1);

   }




   fclose(pFile);

   return count;

}




int getFileMax(char* fileName, int size)

{

   FILE* pFile = fopen_s(&pFile, fileName, "r");

   char temp[10];

   char* a;

   int t;

   int max = 0;

   int count = 0;




   if (pFile != NULL)

   {

      while (!feof(pFile))

      {

         count = 0;

         a = fgets(temp, 10, pFile);

         t = atoi(a);

         while (t > 0) {

            t /= 10;

            count += 1;

         }

         if (max < count) max = count;

      }

   }

   else

   {

      printf("< %s >파일이 존재하지 않습니다.\n", fileName);

      _getch();

      exit(1);

   }

   fclose(pFile);

   return max;

}







int* getFileArr(char* fileName, int size)

{

   FILE* pFile = fopen_s(&pFile, fileName, "r");

   char temp[10];

   int* arr = malloc(sizeof(int) * size);

   char* a;

   int count = 0;

   if (pFile != NULL)

   {

      while (!feof(pFile))

      {

         a = fgets(temp, 10, pFile);

         arr[count++] = atoi(a);

      }

   }

   else

   {

      printf("< %s >파일이 존재하지 않습니다.\n", fileName);

      _getch();

      exit(1);

   }

   fclose(pFile);

   return arr;

}




int getFirstSort()

{

   int select;

   printf("1. 선택정렬\n");

   printf("2. 삽입정렬\n");

   printf("3. 버블정렬\n");

   printf("4. 쉘정렬\n");

   printf("5. 합병정렬\n");

   printf("6. 퀵정렬\n");

   printf("7. 히프정렬\n");

   printf("8. 기수정렬\n");

   printf("0. 종료\n");

   printf("첫번째 정렬을 선택하시오: ");

   scanf_s("%d", &select);

   return select;

}




int getSecondSort()

{

   int select;

   printf("1. 선택정렬\n");

   printf("2. 삽입정렬\n");

   printf("3. 버블정렬\n");

   printf("4. 쉘정렬\n");

   printf("5. 합병정렬\n");

   printf("6. 퀵정렬\n");

   printf("7. 히프정렬\n");

   printf("8. 기수정렬\n");

   printf("0. 종료\n");

   printf("두번째 정렬을 선택하시오: ");

   scanf_s("%d", &select);

   return select;

}




void SortMenu(char* fileName)

{

   

   int size = getFileCount(fileName);

   int* arr = getFileArr(fileName, size);

   int n[2], i;




   n[0] = getFirstSort();

   if (n[0] == 0) return;

   n[1] = getSecondSort();

   if (n[1] == 0) return;




   for (i = 0; i < 2; i++)

   {

      switch (n[i])

      {

      case 1: printf("선택정렬 : %lf초\n", selection_sort(arr, size)); break;

      case 2: printf("삽입정렬 : %lf초\n", insertion_sort(arr, size)); break;

      case 3: printf("버블정렬 : %lf초\n", bubble_sort(arr, size)); break;

      case 4: printf("쉘정렬 : %lf초\n", shell_sort(arr, size)); break;

      case 5:

         initMerge(70001);

         printf("합병정렬 : %lf초\n", merge_sort(arr, 0, size - 1));

         freeMerge();

         break;

      case 6: printf("퀵 정렬 : %lf초\n", quick_sort2(arr, size)); break; //printf("퀵 정렬 : %lf\n", quick_sort(arr, 0, size));

      case 7: printf("히프정렬 : %lf초\n", heap_sort(arr, size)); break;

      case 8: printf("기수정렬 : %lf초\n", radix_sort(arr, size, getFileMax(fileName, size))); break;

      }




   }

}




int menu()

{

   int select;

   system("cls");

   printf("--->2015156007 김석중 자료구조 정렬알고리즘 분석<---");

   printf("=== < Menu > ===\n");

   printf(" 1. 정렬된 파일\n");

   printf(" 2. 역정렬된 파일\n");

   printf(" 3. 랜덤 파일\n");

   printf(">> ");

   scanf_s("%d", &select);

   return select;

}




int main(void)

{

   int select;




   while (1)

   {

      select = menu();

      switch (select)

      {

      case 1: SortMenu("c:\\Users\\main\\Desktop\\Data1.txt"); break;

      case 2: SortMenu("c:\\Users\\main\\Desktop\\Data2.txt"); break;

      case 3: SortMenu("c:\\Users\\main\\Desktop\\Data3.txt"); break;




      }

      printf("계속 하실려면 아무키나 눌러주세요.\n");

      _getch();

   }

}

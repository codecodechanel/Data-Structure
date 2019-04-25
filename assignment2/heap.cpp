//Programming Report #2
//제출인 : 1605020 박소현
//제출날짜 : 2017.11.15(수)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ELEMENT 200

//히프를 1차원 배열로 표현
typedef struct
{
	int key;
}element;

typedef struct
{
	element heap[MAX_ELEMENT];
	int heap_size; //히프 안에 저장된 요소의 개수
}HeapType;

//히프 초기화 함수
void init(HeapType *h)
{
	h->heap_size = 0;
}

//삽입 함수
void insert_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size); //요소가 삽입되기 때문에 힙의 크기가 증가됨.
	
	//트리를 거슬러 올라가면서 부모노드와 비교
	//요소가 1개 이상이고 삽입될 요소의 값과 부모노드의 요소 값과 비교
	while((i!=1) && (item.key > h->heap[i/2].key)) //i번째 노드가 부모노드보다 크면
	{
		h->heap[i] = h->heap[i/2]; //i번째 노드와 부모노드 교환
		i/=2; //한 레벨 위로 승진
	}
	h->heap[i] = item; //새로운 노드 삽입
}

//삭제 함수
element delete_heap(HeapType *h)
{
	int parent, child;
	element item, temp;
	item = h->heap[1]; //루트노드 값의 반환을 위해 루트노드 값을 item에 저장
	temp = h->heap[(h->heap_size)--]; //가장 마지막 노드를 루트 노드로 옮긴 후 힙의 크기를 줄임.
	parent = 1;
	child = 2; //루트의 왼쪽 자신부터 비교 시작

	//왼쪽 자식이 히프 트리의 크기보다 작으면
	while(child <= h->heap_size)
	{
		//왼쪽 자식이 히프 트리를 벗어나지 않고 왼쪽 자식과 오른쪽 자식 중 왼쪽 자식이 더 작으면 if문 실행
		if((child < h->heap_size) && (h->heap[child].key) < h->heap[child+1].key)
			child++; //그 다음 형제노드 검색
		if(temp.key >= h->heap[child].key) //자식노드가 마지막 노드보다 작으면 루프 종료
			break;
		h->heap[parent] = h->heap[child]; //자식노드와 부모노드 교환
		parent = child;
		child *= 2; //다음 레벨로 이동
	}
	h->heap[parent] = temp;
	return item;
}

//히프 정렬 함수
void heap_sort(element a[], int n)
{
	int i;
	HeapType h;
	init(&h);
	for(i=0;i<n;i++)
		insert_heap(&h, a[i]); //히프 삽입
	for(i=(n-1);i>=0;i--)
		a[i] = delete_heap(&h); //히프 삭제를 통한 정렬
}

int main(void)
{
	HeapType heap;
	init(&heap);

	srand(time(NULL));
	element a[30] = {};
	int i, j;
	printf("Input : ");
	for(i=0;i<30;i++)
	{
		a[i].key = 1+(rand()%100);
		insert_heap(&heap, a[i]);
		printf("%d  ", a[i].key);
	}
	printf("\n\n");
	for(j=0;j<30;j++)
	{
		printf("%d  ", a[j].key);
		if(j==0 || j==2 || j==6 || j==14)
			printf("\n");
	}
	printf("\n\n");

	heap_sort(a, 30);

	printf("result : ");
	for(i=0;i<30;i++)
		printf("%d  ", a[i].key);
	printf("\n");
}
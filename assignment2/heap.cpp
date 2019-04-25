//Programming Report #2
//������ : 1605020 �ڼ���
//���⳯¥ : 2017.11.15(��)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_ELEMENT 200

//������ 1���� �迭�� ǥ��
typedef struct
{
	int key;
}element;

typedef struct
{
	element heap[MAX_ELEMENT];
	int heap_size; //���� �ȿ� ����� ����� ����
}HeapType;

//���� �ʱ�ȭ �Լ�
void init(HeapType *h)
{
	h->heap_size = 0;
}

//���� �Լ�
void insert_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size); //��Ұ� ���ԵǱ� ������ ���� ũ�Ⱑ ������.
	
	//Ʈ���� �Ž��� �ö󰡸鼭 �θ���� ��
	//��Ұ� 1�� �̻��̰� ���Ե� ����� ���� �θ����� ��� ���� ��
	while((i!=1) && (item.key > h->heap[i/2].key)) //i��° ��尡 �θ��庸�� ũ��
	{
		h->heap[i] = h->heap[i/2]; //i��° ���� �θ��� ��ȯ
		i/=2; //�� ���� ���� ����
	}
	h->heap[i] = item; //���ο� ��� ����
}

//���� �Լ�
element delete_heap(HeapType *h)
{
	int parent, child;
	element item, temp;
	item = h->heap[1]; //��Ʈ��� ���� ��ȯ�� ���� ��Ʈ��� ���� item�� ����
	temp = h->heap[(h->heap_size)--]; //���� ������ ��带 ��Ʈ ���� �ű� �� ���� ũ�⸦ ����.
	parent = 1;
	child = 2; //��Ʈ�� ���� �ڽź��� �� ����

	//���� �ڽ��� ���� Ʈ���� ũ�⺸�� ������
	while(child <= h->heap_size)
	{
		//���� �ڽ��� ���� Ʈ���� ����� �ʰ� ���� �ڽİ� ������ �ڽ� �� ���� �ڽ��� �� ������ if�� ����
		if((child < h->heap_size) && (h->heap[child].key) < h->heap[child+1].key)
			child++; //�� ���� ������� �˻�
		if(temp.key >= h->heap[child].key) //�ڽĳ�尡 ������ ��庸�� ������ ���� ����
			break;
		h->heap[parent] = h->heap[child]; //�ڽĳ��� �θ��� ��ȯ
		parent = child;
		child *= 2; //���� ������ �̵�
	}
	h->heap[parent] = temp;
	return item;
}

//���� ���� �Լ�
void heap_sort(element a[], int n)
{
	int i;
	HeapType h;
	init(&h);
	for(i=0;i<n;i++)
		insert_heap(&h, a[i]); //���� ����
	for(i=(n-1);i>=0;i--)
		a[i] = delete_heap(&h); //���� ������ ���� ����
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
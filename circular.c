/*
 * circularQ.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4

typedef char element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;


QueueType* createQueue();
int freeQueue(QueueType* cQ);
int isEmpty(QueueType* cQ);
int isFull(QueueType* cQ);
void enQueue(QueueType* cQ, element item);
void deQueue(QueueType* cQ, element* item);
void printQ(QueueType* cQ);
void debugQ(QueueType* cQ);
element getElement();

int main(void)
{
	QueueType* cQ = createQueue();
	element data;
	char command;

	printf("[----- [������] [2018038027] -----]\n");


	do {
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D':
			deQueue(cQ, &data);
			break;
		case 'p': case 'P':
			printQ(cQ);
			break;
		case 'b': case 'B':
			debugQ(cQ);
			break;
		case 'q': case 'Q':
			freeQueue(cQ);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');


	return 1;
}

QueueType* createQueue()//���� ť�� �����.
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType));//���� �Ҵ��� ���Ͽ� ���� ť�� �����ϴ� �Լ�
	cQ->front = 0;//front�� �ʱⰪ�� 0
	cQ->rear = 0;//rear�� �ʱⰪ�� 0
	return cQ;
}

int freeQueue(QueueType* cQ)//�����Ҵ����� ������ ���� ť�� ���� �ϴ� �Լ�
{
	if (cQ == NULL) return 1;
	free(cQ);//�����Ҵ��� ����
	return 1;
}

element getElement()//item�� ���� �޾��ִ� �Լ�
{
	element item;
	printf("Input element = ");
	fflush(stdout);
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType* cQ)
{
	if (cQ->front == cQ->rear){//���� front�� rear�� ���� ���ٸ�
		printf("Que is empty!");
		return -1;
	}//Que�� ����ٴ� ������ ����Ѵ�.
	else
		return 0;
}

/* complete the function */
int isFull(QueueType* cQ)
{
	if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front){//���� rear�� 1�� ���Ͽ� MAX_QUEUE_SIZE�� ���� �������� front�� ���ٸ�(��=0�̶��)
		printf("Que is full!");
		return -1;
	}//Que�� ��á�ٴ� ������ ����Ѵ�.
	else
		return 0;
}


/* complete the function */
void enQueue(QueueType* cQ, element item)//ť�� ���� ��� �Լ�
{
	if(isFull(cQ))
	{
		return;
	}
	else{
    cQ->rear = (cQ->rear + 1) % (MAX_QUEUE_SIZE);//���� ť������ MAX_QUEUE_SIZE-1�� �ش��ϴ� �ε��� ���� 0�� �Ǿ���ϹǷ� ��ⷯ ������ ���� ������ �� �ִ�.
	cQ->queue[cQ->rear] = item;
	}
}

/* complete the function */
void deQueue(QueueType* cQ, element* item)
{
	if(isEmpty(cQ))//���� ť�� ����ִٸ� isEmpty �Լ��� ����
	{
		return;

	}
	*item = cQ->queue[cQ->front];//���� front�� ���� �ε����� �ִ� ���� item�� ����Ű�� ������ �ű��.
	cQ->front = (cQ->front + 1) % (MAX_QUEUE_SIZE);//��ⷯ ������ ���� front�� ���� �÷��ش�.
}


void printQ(QueueType* cQ)//ť�� ����ϴ� �Լ�
{
	int i, first, last;

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;

	printf("Circular Queue : [");

	i = first;
	while (i != last) {
		printf("%3c", cQ->queue[i]);
		i = (i + 1) % MAX_QUEUE_SIZE;

	}
	printf(" ]\n");
}


void debugQ(QueueType* cQ)//ť�� ���� ���¸� ����ϴ� �Լ�
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if (i == cQ->front) {
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

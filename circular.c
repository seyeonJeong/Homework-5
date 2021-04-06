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

	printf("[----- [정세연] [2018038027] -----]\n");


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

QueueType* createQueue()
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType));
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType* cQ)
{
	if (cQ == NULL) return 1;
	free(cQ);
	return 1;
}

element getElement()
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
	if (cQ->front == cQ->rear){//만약 front와 rear의 값이 같다면
		printf("Que is empty!");
		return -1;
	}//Que가 비었다는 문장을 출력한다.
	else
		return 0;
}

/* complete the function */
int isFull(QueueType* cQ)
{
	if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front){//만약 rear에 1을 더하여 MAX_QUEUE_SIZE로 나눈 나머지가 front와 같다면(즉=0이라면)
		printf("Que is full!");
		return -1;
	}//Que가 꽉찼다는 문장을 출력한다.
	else
		return 0;
}


/* complete the function */
void enQueue(QueueType* cQ, element item)
{
	if(isFull(cQ))
	{
		return;
	}
	else{
    cQ->rear = (cQ->rear + 1) % (MAX_QUEUE_SIZE);//원형 큐에서는 MAX_QUEUE_SIZE-1에 해당하는 인덱스 다음 0이 되어야하므로 이런식의 계산으로 rear의 값을 추가해준다
	cQ->queue[cQ->rear] = item;
	}
}

/* complete the function */
void deQueue(QueueType* cQ, element* item)
{
	if(isEmpty(cQ))
	{
		return;

	}
	*item = cQ->queue[cQ->front];//원래 front의 값의 인덱스에 있던 값을 item이 가리키는 곳으로 옮긴다.
	cQ->front = (cQ->front + 1) % (MAX_QUEUE_SIZE);//front의 값을 늘려준다.
}


void printQ(QueueType* cQ)
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


void debugQ(QueueType* cQ)
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

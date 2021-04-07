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

QueueType* createQueue()//원형 큐를 생성
{
	QueueType* cQ;
	cQ = (QueueType*)malloc(sizeof(QueueType));//동적할당을 통해 원형 큐의 메모리를 할당
	//front와 rear의 초기값은 0
	cQ->front = 0;
	cQ->rear = 0;
	return cQ;
}

int freeQueue(QueueType* cQ)//원형큐를 해제해주는 함수
{
	if (cQ == NULL) return 1;//비어있다면 해제하지않음.
	free(cQ);//원형큐를 해제
	return 1;
}

element getElement()//원소를 받아주는 함수
{
	element item;
	printf("Input element = ");
	fflush(stdout);
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType* cQ)//원형큐가 비었는지 확인하는 함수
{
	if (cQ->front == cQ->rear){//만약 front와 rear의 값이 같다면
		printf("Que is empty!");
		return -1;
	}//Que가 비었다는 문장을 출력한다.
	else
		return 0;
}

/* complete the function */
int isFull(QueueType* cQ)//원형큐가 포화상태인지 확인하는 함수
{
	if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front){//만약 rear에 1을 더하여 MAX_QUEUE_SIZE로 나눈 나머지가 front와 같다면(즉=0이라면)
		printf("Que is full!");
		return -1;
	}//Que가 꽉찼다는 문장을 출력한다.
	else
		return 0;
}


/* complete the function */
void enQueue(QueueType* cQ, element item)//큐에 데이터를 넣어주는 기능 (stack에서의 push)
{
	if(isFull(cQ))
	{
		return;
	}
	else{
    cQ->rear = (cQ->rear + 1) % (MAX_QUEUE_SIZE);//원형 큐에서는 MAX_QUEUE_SIZE-1의 다음값이 0이 되어야 하는데 1씩 더하는 방법으로는 구현할 수 없어 모듈러 연산(나머지값)을 통해 증가연산을 구현할 수 있다.
	cQ->queue[cQ->rear] = item;//queue의 rear값에 해당하는 배열에 item을 대입시켜준다.
	}
}

/* complete the function */
void deQueue(QueueType* cQ, element* item)//큐에 데이터를 빼주는 기능
{
	if(isEmpty(cQ))
	{
		return;

	}
	*item = cQ->queue[cQ->front];//원래 front의 값의 인덱스에 있던 값을 item이 가리키는 곳으로 옮긴다.
	cQ->front = (cQ->front + 1) % (MAX_QUEUE_SIZE);//front의 값을 늘려준다.
}


void printQ(QueueType* cQ)//큐를 출력해주는 함수
{
	int i, first, last;//정수형 변수 3개 선언

	first = (cQ->front + 1) % MAX_QUEUE_SIZE;//모듈러 연산을 통해 first에 값을 삽입한다.
	last = (cQ->rear + 1) % MAX_QUEUE_SIZE;//모듈러 연산을 통해 last에 값을 삽입한다.

	printf("Circular Queue : [");

	i = first;//i에 first의 값을 대입한다.
	while (i != last) {//i가 last가 아닐때까지
		printf("%3c", cQ->queue[i]);//queue[i]의 값을 출력
		i = (i + 1) % MAX_QUEUE_SIZE;//모듈러 연산을 통해 i의 값을 늘려준다

	}
	printf(" ]\n");
}


void debugQ(QueueType* cQ)//큐의 상태를 확인할 수 있게 해주는 함수
{

	printf("\n---DEBUG\n");
	for (int i = 0; i < MAX_QUEUE_SIZE; i++)//반복문을 이용하여 큐에 들어있는 데이터를 출력해준다.
	{
		if (i == cQ->front) {//큐의 front와 i가 같다면
			printf("  [%d] = front\n", i);
			continue;
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);
}

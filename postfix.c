/*
 * postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixpush(char x);
char postfixPop();
void evalPush(int x);
int evalPop();
void getInfix();
precedence getToken(char symbol);
precedence getPriority(char x);
void charCat(char* c);
void toPostfix();
void debug();
void reset();
void evaluation();

int main()
{
	char command;

	printf("[----- [정세연] [2018038027] -----]\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		fflush(stdout);
		scanf(" %c", &command);

		switch (command) {
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

void postfixPush(char x)
{
	postfixStack[++postfixStackTop] = x;
}

char postfixPop()//stack의 pop을 해주는 함수
{
	char x;
	if (postfixStackTop == -1)//만약 stack의 top이 비었다면
		return '\0';//pop을 할 수 없음
	else {
		x = postfixStack[postfixStackTop--];//x에 postfixStack의 현재 top값을 대입하고 top의 값을 1줄임
	}
	return x;//x를 반환
}

void evalPush(int x)//evaluation의 함수에서 stack에 push를 해주는 함수
{
	evalStack[++evalStackTop] = x;//evalStack이라는 스택에 top의 값을 1증가시킨 후 정수형 x를 대입한다.
}

int evalPop()//evaluation의 함수에서 stack에 pop을 해주는 함수
{
	if (evalStackTop == -1)//만약 top이 -1 즉 stack에 값이 없다면 pop을 해줄 수 없음
		return -1;
	else
		return evalStack[evalStackTop--];//evalStack의 현재 top값을 리턴하고 1줄임.
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix()//infix에 해당하는 값을 받아주는 함수
{
	printf("Type the expression >>> ");
	fflush(stdout);
	scanf("%s", infixExp);
}

precedence getToken(char symbol)//구조체 자료형을 갖는 함수, 연산자의 형태에 따른 return 값을 갖는다.
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;//피연산자이면 operand를 리턴
	}
}

precedence getPriority(char x)//구조체 자료형을 갖는 함수, char형 함수를 받아 getToken에 전달한다.
{
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);//postfixExp배열의 하나의 문자 복사
	else
		strncat(postfixExp, c, 1);//postfixExp배열의 하나의 문자 붙이기
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char* exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	int pri[] = { 1,1,1,1,2,2,4,4,1,1 };
	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while (*exp != '\0')
	{
		if (getToken(*exp) == lparen)//만약 문자가 '('이면
		{
			postfixPush(*exp);//'('를 push 한다
			exp++;//exp를 1씩 증가
		}
		else if (getToken(*exp) == operand)//만약 피연산자이면
		{
			charCat(exp);//*exp를 전달받아 postfixExp에 추가
			exp++;//exp를 1씩 증가
		}
		else if (getToken(*exp) == rparen)//만약 문자가 ')'이면
		{
			do
			{
				x = postfixPop();//postfixpop함수의 값을 x에 저장
				if (getToken(x) != lparen)//만약 x의 값이 '('이 아니면
					charCat(&x);//스택에서 pop을 해줌(x가 postfixpop함수이므로)
				else
					break;
			} while (1);
			exp++;//exp를 1씩 증가
		}
		else// 숫자와 '(',')'이 아니라면(ex : +, -, /, ..etc)
		{
			while (postfixStackTop != -1 && pri[getPriority(postfixStack[postfixStackTop])] >= pri[getPriority(*exp)]) {
				x = postfixPop();//postfixpop함수의 값을 x에 저장
				charCat(&x);//스택에서 pop을 해줌 (x가 postfixpop함수이므로)
			}//스택에서 top에 속해있는 우선순위와 현재 *exp의 값의 우선순위를 비교한다.

			postfixPush(*exp);//스택이 비어있다면 push를 해줌
			exp++;//exp를 1증가
		}
	}
	while ((postfixStackTop != -1))//stack의 top이 -1이 아닐 때까지 반복
	{
		x = postfixPop();
		charCat(&x);//스택에서 pop을 한다.
	}
}
void debug()//디버그를 해주는 함수
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)//stack의 값을 반복문을 통하여 출력
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()//리셋을 해주는 함수
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)//반복문을 통하여 stack을 리셋
		postfixStack[i] = '\0';

	//top의 값들을 다시 원래대로 -1로 설정
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()//postfixExp에서 피연산자를 pop시켜 연산을 수행하는 함수
{
	int op1, op2;
	int n = 0;
	char* token = postfixExp;

	while (*token != '\0')
	{
		if (getToken(*token) == operand)//만약 피연산자이면 조건문안에있는 연산을 수행
		{
			n = *token;
			evalPush(n - 48);//아스키코드상 문자가 48번째 부터 이므로 48을 빼주어서 숫자로 표현

		}
		else//두 피연산자를 pop 연산을 수행한 후 , 그 결과를 스택에 삽입함.
		{
			op2 = evalPop();//스택 pop
			op1 = evalPop();//스택 pop
			switch (getToken(*token))
			{
			case times://곱셈일 경우
				evalPush(op1 * op2);//pop된 두 피연산자를 곱해줌
				break;
			case divide:
				evalPush(op1 / op2);//pop된 두 피연산자를 나눠줌
				break;
			case  plus:
				evalPush(op1 + op2);//pop된 두 피연산자를 더해줌
				break;
			case minus:
				evalPush(op1 - op2);//pop된 두 피연산자를 빼줌
				break;
			}

		}
		token++;//token의 값을 증가
	}
	evalResult = evalPop();//마지막 연산 값을 evalResult에 저장
}

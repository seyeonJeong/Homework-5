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

 /* stack ������ �켱����, lparen = 0 ���� ���� */
typedef enum {
	lparen = 0,  /* ( ���� ��ȣ */
	rparen = 9,  /* ) ������ ��ȣ*/
	times = 7,   /* * ���� */
	divide = 6,  /* / ������ */
	plus = 5,    /* + ���� */
	minus = 4,   /* - ���� */
	operand = 1 /* �ǿ����� */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression�� �����ϴ� �迭 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix�� ����� ���ڿ��� �����ϴ� �迭 */
char postfixStack[MAX_STACK_SIZE];	/* postfix�� ��ȯ�� ���� �ʿ��� ���� */
int evalStack[MAX_STACK_SIZE];		/* ����� ���� �ʿ��� ���� */

int postfixStackTop = -1;  /* postfixStack�� top */
int evalStackTop = -1;	   /* evalStack�� top */

int evalResult = 0;	   /* ��� ����� ���� */

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

	printf("[----- [������] [2018038027] -----]\n");

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

char postfixPop()//stack�� pop�� ���ִ� �Լ�
{
	char x;
	if (postfixStackTop == -1)//���� stack�� top�� ����ٸ�
		return '\0';//pop�� �� �� ����
	else {
		x = postfixStack[postfixStackTop--];//x�� postfixStack�� ���� top���� �����ϰ� top�� ���� 1����
	}
	return x;//x�� ��ȯ
}

void evalPush(int x)//evaluation�� �Լ����� stack�� push�� ���ִ� �Լ�
{
	evalStack[++evalStackTop] = x;//evalStack�̶�� ���ÿ� top�� ���� 1������Ų �� ������ x�� �����Ѵ�.
}

int evalPop()//evaluation�� �Լ����� stack�� pop�� ���ִ� �Լ�
{
	if (evalStackTop == -1)//���� top�� -1 �� stack�� ���� ���ٸ� pop�� ���� �� ����
		return -1;
	else
		return evalStack[evalStackTop--];//evalStack�� ���� top���� �����ϰ� 1����.
}

/**
 * infix expression�� �Է¹޴´�.
 * infixExp���� �Էµ� ���� �����Ѵ�.
 */
void getInfix()//infix�� �ش��ϴ� ���� �޾��ִ� �Լ�
{
	printf("Type the expression >>> ");
	fflush(stdout);
	scanf("%s", infixExp);
}

precedence getToken(char symbol)//����ü �ڷ����� ���� �Լ�, �������� ���¿� ���� return ���� ���´�.
{
	switch (symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	default: return operand;//�ǿ������̸� operand�� ����
	}
}

precedence getPriority(char x)//����ü �ڷ����� ���� �Լ�, char�� �Լ��� �޾� getToken�� �����Ѵ�.
{
	return getToken(x);
}

/**
 * �����ϳ��� ���޹޾�, postfixExp�� �߰�
 */
void charCat(char* c)
{
	if (postfixExp == '\0')
		strncpy(postfixExp, c, 1);//postfixExp�迭�� �ϳ��� ���� ����
	else
		strncat(postfixExp, c, 1);//postfixExp�迭�� �ϳ��� ���� ���̱�
}

/**
 * infixExp�� ���ڸ� �ϳ��� �о�鼭 stack�� �̿��Ͽ� postfix�� �����Ѵ�.
 * ����� postfix�� postFixExp�� ����ȴ�.
 */
void toPostfix()
{
	/* infixExp�� ���� �ϳ����� �б����� ������ */
	char* exp = infixExp;
	char x; /* �����ϳ��� �ӽ÷� �����ϱ� ���� ���� */
	int pri[] = { 1,1,1,1,2,2,4,4,1,1 };
	/* exp�� �������Ѱ��鼭, ���ڸ� �а� postfix�� ���� */
	while (*exp != '\0')
	{
		if (getToken(*exp) == lparen)//���� ���ڰ� '('�̸�
		{
			postfixPush(*exp);//'('�� push �Ѵ�
			exp++;//exp�� 1�� ����
		}
		else if (getToken(*exp) == operand)//���� �ǿ������̸�
		{
			charCat(exp);//*exp�� ���޹޾� postfixExp�� �߰�
			exp++;//exp�� 1�� ����
		}
		else if (getToken(*exp) == rparen)//���� ���ڰ� ')'�̸�
		{
			do
			{
				x = postfixPop();//postfixpop�Լ��� ���� x�� ����
				if (getToken(x) != lparen)//���� x�� ���� '('�� �ƴϸ�
					charCat(&x);//���ÿ��� pop�� ����(x�� postfixpop�Լ��̹Ƿ�)
				else
					break;
			} while (1);
			exp++;//exp�� 1�� ����
		}
		else// ���ڿ� '(',')'�� �ƴ϶��(ex : +, -, /, ..etc)
		{
			while (postfixStackTop != -1 && pri[getPriority(postfixStack[postfixStackTop])] >= pri[getPriority(*exp)]) {
				x = postfixPop();//postfixpop�Լ��� ���� x�� ����
				charCat(&x);//���ÿ��� pop�� ���� (x�� postfixpop�Լ��̹Ƿ�)
			}//���ÿ��� top�� �����ִ� �켱������ ���� *exp�� ���� �켱������ ���Ѵ�.

			postfixPush(*exp);//������ ����ִٸ� push�� ����
			exp++;//exp�� 1����
		}
	}
	while ((postfixStackTop != -1))//stack�� top�� -1�� �ƴ� ������ �ݺ�
	{
		x = postfixPop();
		charCat(&x);//���ÿ��� pop�� �Ѵ�.
	}
}
void debug()//����׸� ���ִ� �Լ�
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for (int i = 0; i < MAX_STACK_SIZE; i++)//stack�� ���� �ݺ����� ���Ͽ� ���
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset()//������ ���ִ� �Լ�
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for (int i = 0; i < MAX_STACK_SIZE; i++)//�ݺ����� ���Ͽ� stack�� ����
		postfixStack[i] = '\0';

	//top�� ������ �ٽ� ������� -1�� ����
	postfixStackTop = -1;
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation()//postfixExp���� �ǿ����ڸ� pop���� ������ �����ϴ� �Լ�
{
	int op1, op2;
	int n = 0;
	char* token = postfixExp;

	while (*token != '\0')
	{
		if (getToken(*token) == operand)//���� �ǿ������̸� ���ǹ��ȿ��ִ� ������ ����
		{
			n = *token;
			evalPush(n - 48);//�ƽ�Ű�ڵ�� ���ڰ� 48��° ���� �̹Ƿ� 48�� ���־ ���ڷ� ǥ��

		}
		else//�� �ǿ����ڸ� pop ������ ������ �� , �� ����� ���ÿ� ������.
		{
			op2 = evalPop();//���� pop
			op1 = evalPop();//���� pop
			switch (getToken(*token))
			{
			case times://������ ���
				evalPush(op1 * op2);//pop�� �� �ǿ����ڸ� ������
				break;
			case divide:
				evalPush(op1 / op2);//pop�� �� �ǿ����ڸ� ������
				break;
			case  plus:
				evalPush(op1 + op2);//pop�� �� �ǿ����ڸ� ������
				break;
			case minus:
				evalPush(op1 - op2);//pop�� �� �ǿ����ڸ� ����
				break;
			}

		}
		token++;//token�� ���� ����
	}
	evalResult = evalPop();//������ ���� ���� evalResult�� ����
}

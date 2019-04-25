/*����� : �ڷᱸ��
  �й� : 02�й�
  ��米�� : ���� ������
  ���� ���� : HW #2
  ���α׷��� ������ : ����ǥ��� ����ǥ������� ��ȯ�� �� ��갪 ����ϱ�
  �������� : 2017.10.11(��)

  �а� : ������а�
  �й� : 1605020
  �̸� : �ڼ���
  �̸��� �ּ� : kangil0911@naver.com
  ����ó: 010-7258-8739
*/

#include <stdio.h>
#include <string.h> //���ڿ��� ����ϱ� ����
#include <math.h> //pow �Լ��� ����ϱ� ����

#define MAX_STACK_SIZE 100

typedef char element;

//����ü�� �������ش�.
typedef struct{
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

//������ �ʱ�ȭ���ش�.
void init(StackType *s)
{
	s->top = -1; //s->top�� -1�� ����Ű�� ����ִٴ� ���̴�. 
}
//������ ���� ���ִ����� Ȯ�����ش�.
int is_full(StackType *s)
{
	return s->top == MAX_STACK_SIZE;
}
//������ top�� -1�� ����Ű�� ����ִٴ� ���̴�.
int is_empty(StackType *s)
{
	return s->top == -1;
}
//���� �ȿ� ��ҵ��� �־��ش�.
//������ ������ ��� ���ִٴ� �޼����� ����ϰ�, �׷��� ���� ��쿡�� �� ���� ��Ҹ� �������ش�.
void push(StackType *s, element item)
{
	if(is_full(s))
	{
		printf("stack is full!\n");
	}
	else
		s->stack[++(s->top)] = item; //s->top�� ����Ű�� �� �� ĭ ���� ��Ҹ� �������ش�.
}

//���� �ȿ� �ִ� ����� ���� ��ȯ�ϰ� �������ش�.
//������ ������� ��쿡�� ����ִٴ� �޼����� ����ϰ�, �׷��� ���� ��쿡�� top�� ����Ű�� ���� ��ȯ�ϰ� �������ش�.
element pop(StackType *s)
{
	if(is_empty(s))
		printf("Stack is empty!!\n");
	else
		return s->stack[(s->top)--];
}

//
element peek(StackType *s)
{
	if(is_empty(s))
		printf("Stack is empty!!\n");
	else
		return s->stack[s->top];
}

//�����ڵ��� �켱������ �����ش�.
int prec(char op)
{
	//���ϰ��� Ŭ���� �������� �켱������ �� ũ��.
	switch(op)
	{
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
	case '%':
		return 2;
	case '^':
		return 3; 
	}
	return -1;
}

//����ǥ����� ����ǥ������� ��ȯ���ش�.
char* infix_to_postfix(char exp[])
{
	int i=0;
	char ch, top_op;
	int length = strlen(exp);
	StackType s;
	char result[MAX_STACK_SIZE] = "";
	int j=0;

	init(&s);
	//for���� ���� �����ڵ��� �켱������ ���� push�� pop�� �������ְ�, ���� ��ȣ�� ������ ������ push, ������ ��ȣ�� ������ ���� ���� ��ȣ�� ���� ������ pop���ش�.
	for(i=0;i<(length-1);i++)
	{
		ch = exp[i];
		switch(ch)
		{
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '%':
			while(!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
				result[j++] = pop(&s);
			push(&s, ch);
			break;
		case '(': 
			push(&s, ch); //���� ��ȣ�� ��� ������ ���ÿ� �����Ѵ�.
			break;
		case ')':
			top_op = pop(&s);
			while(top_op != '(')
			{
				result[j++] = top_op;
				top_op = pop(&s);
			} //������ ��ȣ�� ��� ���� ��ȣ�� ���� ������ pop���ش�.
			break;
		default:
			result[j++] = ch;
			break;
		}
	}
	//���� �����ڴ� ��� pop���ش�.
	while(!is_empty(&s))
		result[j++] = pop(&s);
	return result;
}

//���� ����Ͽ� �� ���� ��ȯ���ش�.
 int eval(char exp[])
{
	int op1, op2, value, i=0;
	int len = strlen(exp);
	char ch;
	StackType s;

	init(&s);
	for(i=0;i<len;i++)
	{
		ch = exp[i];
		if(ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '^' && ch != '%')
		{
			value = ch-'0';
			push(&s, value);
		} //�����ڰ� �ƴ� ��쿡�� ���ÿ� �������ش�.
		else
		{
			op2 = pop(&s);
			op1 = pop(&s);
			switch(ch)
			{
			case '+':
				push(&s, op1+op2);
				break;
			case '-':
				push(&s, op1-op2);
				break;
			case '*':
				push(&s, op1*op2);
				break;
			case '/':
				push(&s, op1/op2);
				break;
			case '^':
				push(&s, pow((double)op1, (double)op2));
				break;
			case '%':
				push(&s, op1%op2);
				break;
			} //�����ڿ� ���� ���갪�� ���ÿ� push���ش�.
		}
	}
	return pop(&s); //������ ������ ���, ��, ������� pop���־� main�Լ��� �������ش�.
}

int main(void)
{
	StackType s;
	init(&s);
	char ch;
	char exp[MAX_STACK_SIZE];
	char postfix[MAX_STACK_SIZE];
	
	printf("-------------------------------------------\n");
	//�ؽ�Ʈ ������ �б� ���� �ҷ��� FILE *fp1�� �������ش�.
	FILE *fp1 = fopen("infix1.txt", "r");
	printf("<infix1 �ؽ�Ʈ ����>\n");
	char num1 = fgetc(fp1); //�ؽ�Ʈ ���Ϸκ��� ���� �ϳ��� �޾ƿ´�. ���⼭�� ������� ���� �ǹ�.
	printf("\n������� ���� : %c\n", num1);
	
	//for���� ���� ���� ����ĵ��� �� ���徿 ���ʴ�� ó�����ش�.
	for(char i='0';i<num1;i++)
	{
		//����� �� ������ exp�� �־��ش�.
		fscanf(fp1, "%s", &exp);
		printf("\ninfix notation = %s\n", exp);
		//�Լ��� ȣ���Ͽ� ����ǥ����� ����ǥ������� ��ȯ���ش�.
		infix_to_postfix(exp);
		strncpy(postfix, infix_to_postfix(exp), strlen(infix_to_postfix(exp))); //����ǥ����� postfix��� ���ο� �迭�� �������ش�.
		postfix[strlen(infix_to_postfix(exp))] = '\0'; //���� NULL�� �ٿ��� �迭�� ���� �˸� �� �ֵ��� �Ѵ�.
		printf("postfix notation = %s\n", postfix);
		printf("result = %d\n", eval(postfix));
	}
	printf("-------------------------------------------\n");

	FILE *fp2 = fopen("infix2.txt", "r");
	printf("<infix2 �ؽ�Ʈ ����>\n");
	char num2 = fgetc(fp2);
	printf("\n������� ���� : %c\n", num2);
	for(char i='0';i<num2;i++)
	{
		fscanf(fp2, "%s", &exp);
		printf("\ninfix notation = %s\n", exp);
		infix_to_postfix(exp);
		strncpy(postfix, infix_to_postfix(exp), strlen(infix_to_postfix(exp)));
		postfix[strlen(infix_to_postfix(exp))] = '\0';
		printf("postfix notation = %s\n", postfix);
		printf("result = %d\n", eval(postfix));
	} //���� ����.
	printf("-------------------------------------------\n");

	FILE *fp3 = fopen("infix3.txt", "r");
	printf("<infix3 �ؽ�Ʈ ����>\n");
	char num3 = fgetc(fp3);
	printf("\n������� ���� : %c\n", num3);
	for(char i='0';i<num3;i++)
	{
		fscanf(fp3, "%s", &exp);
		printf("\ninfix notation = %s\n", exp);
		infix_to_postfix(exp);
		strncpy(postfix, infix_to_postfix(exp), strlen(infix_to_postfix(exp)));
		postfix[strlen(infix_to_postfix(exp))] = '\0';
		printf("postfix notation = %s\n", postfix);
		printf("result = %d\n", eval(postfix));
	} //���� ����.
	return 0;
}

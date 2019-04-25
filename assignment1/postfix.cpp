/*과목명 : 자료구조
  분반 : 02분반
  담당교수 : 김경아 교수님
  과제 차수 : HW #2
  프로그래밍 과제명 : 중위표기식 후위표기식으로 변환한 후 계산값 출력하기
  제출일자 : 2017.10.11(수)

  학과 : 건축공학과
  학번 : 1605020
  이름 : 박소현
  이메일 주소 : kangil0911@naver.com
  연락처: 010-7258-8739
*/

#include <stdio.h>
#include <string.h> //문자열을 사용하기 위해
#include <math.h> //pow 함수를 사용하기 위해

#define MAX_STACK_SIZE 100

typedef char element;

//구조체를 선언해준다.
typedef struct{
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

//스택을 초기화해준다.
void init(StackType *s)
{
	s->top = -1; //s->top이 -1을 가리키면 비어있다는 뜻이다. 
}
//스택이 가득 차있는지를 확인해준다.
int is_full(StackType *s)
{
	return s->top == MAX_STACK_SIZE;
}
//스택의 top이 -1을 가리키면 비어있다는 뜻이다.
int is_empty(StackType *s)
{
	return s->top == -1;
}
//스택 안에 요소들을 넣어준다.
//스택이 차있을 경우 차있다는 메세지를 출력하고, 그렇지 않은 경우에는 맨 위에 요소를 삽입해준다.
void push(StackType *s, element item)
{
	if(is_full(s))
	{
		printf("stack is full!\n");
	}
	else
		s->stack[++(s->top)] = item; //s->top이 가리키는 곳 한 칸 위에 요소를 삽입해준다.
}

//스택 안에 있는 요소의 값을 반환하고 삭제해준다.
//스택이 비어있을 경우에는 비어있다는 메세지를 출력하고, 그렇지 않은 경우에는 top이 가리키는 값을 반환하고 삭제해준다.
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

//연산자들의 우선순위를 정해준다.
int prec(char op)
{
	//리턴값이 클수록 연산자의 우선순위가 더 크다.
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

//중위표기식을 후위표기식으로 변환해준다.
char* infix_to_postfix(char exp[])
{
	int i=0;
	char ch, top_op;
	int length = strlen(exp);
	StackType s;
	char result[MAX_STACK_SIZE] = "";
	int j=0;

	init(&s);
	//for문을 돌며 연산자들의 우선순위에 따라 push와 pop을 결정해주고, 왼쪽 괄호일 때에는 무조건 push, 오른쪽 괄호가 나왔을 때는 왼쪽 괄호가 나올 때까지 pop해준다.
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
			push(&s, ch); //왼쪽 괄호일 경우 무조건 스택에 삽입한다.
			break;
		case ')':
			top_op = pop(&s);
			while(top_op != '(')
			{
				result[j++] = top_op;
				top_op = pop(&s);
			} //오른쪽 괄호일 경우 왼쪽 괄호가 나올 때까지 pop해준다.
			break;
		default:
			result[j++] = ch;
			break;
		}
	}
	//남은 연산자는 모두 pop해준다.
	while(!is_empty(&s))
		result[j++] = pop(&s);
	return result;
}

//식을 계산하여 그 값을 반환해준다.
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
		} //연산자가 아닐 경우에는 스택에 삽입해준다.
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
			} //연산자에 따른 연산값을 스택에 push해준다.
		}
	}
	return pop(&s); //스택의 마지막 요소, 즉, 결과값을 pop해주어 main함수로 리턴해준다.
}

int main(void)
{
	StackType s;
	init(&s);
	char ch;
	char exp[MAX_STACK_SIZE];
	char postfix[MAX_STACK_SIZE];
	
	printf("-------------------------------------------\n");
	//텍스트 파일을 읽기 모드로 불러와 FILE *fp1에 저장해준다.
	FILE *fp1 = fopen("infix1.txt", "r");
	printf("<infix1 텍스트 파일>\n");
	char num1 = fgetc(fp1); //텍스트 파일로부터 문자 하나를 받아온다. 여기서는 연산식의 개수 의미.
	printf("\n연산식의 개수 : %c\n", num1);
	
	//for문을 돌며 안의 연산식들을 한 문장씩 차례대로 처리해준다.
	for(char i='0';i<num1;i++)
	{
		//연산식 한 문장을 exp에 넣어준다.
		fscanf(fp1, "%s", &exp);
		printf("\ninfix notation = %s\n", exp);
		//함수를 호출하여 중위표기식을 후위표기식으로 변환해준다.
		infix_to_postfix(exp);
		strncpy(postfix, infix_to_postfix(exp), strlen(infix_to_postfix(exp))); //후위표기식을 postfix라는 새로운 배열에 저장해준다.
		postfix[strlen(infix_to_postfix(exp))] = '\0'; //끝에 NULL을 붙여서 배열의 끝을 알릴 수 있도록 한다.
		printf("postfix notation = %s\n", postfix);
		printf("result = %d\n", eval(postfix));
	}
	printf("-------------------------------------------\n");

	FILE *fp2 = fopen("infix2.txt", "r");
	printf("<infix2 텍스트 파일>\n");
	char num2 = fgetc(fp2);
	printf("\n연산식의 개수 : %c\n", num2);
	for(char i='0';i<num2;i++)
	{
		fscanf(fp2, "%s", &exp);
		printf("\ninfix notation = %s\n", exp);
		infix_to_postfix(exp);
		strncpy(postfix, infix_to_postfix(exp), strlen(infix_to_postfix(exp)));
		postfix[strlen(infix_to_postfix(exp))] = '\0';
		printf("postfix notation = %s\n", postfix);
		printf("result = %d\n", eval(postfix));
	} //위와 같다.
	printf("-------------------------------------------\n");

	FILE *fp3 = fopen("infix3.txt", "r");
	printf("<infix3 텍스트 파일>\n");
	char num3 = fgetc(fp3);
	printf("\n연산식의 개수 : %c\n", num3);
	for(char i='0';i<num3;i++)
	{
		fscanf(fp3, "%s", &exp);
		printf("\ninfix notation = %s\n", exp);
		infix_to_postfix(exp);
		strncpy(postfix, infix_to_postfix(exp), strlen(infix_to_postfix(exp)));
		postfix[strlen(infix_to_postfix(exp))] = '\0';
		printf("postfix notation = %s\n", postfix);
		printf("result = %d\n", eval(postfix));
	} //위와 같다.
	return 0;
}

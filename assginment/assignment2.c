#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_EXPR 1000
#define MAX_STACK 1000

// 연산자 우선순위
int precedence(char op)
{
  switch (op)
  {
  case '+':
  case '-':
    return 1;
  case '*':
  case '/':
    return 2;
  case '^':
    return 3;
  default:
    return 0;
  }
}

// 스택 관련 함수
void push(char stack[], int *top, char value)
{
  stack[++(*top)] = value;
}

char pop(char stack[], int *top)
{
  return stack[(*top)--];
}

char peek(char stack[], int top)
{
  return stack[top];
}

// 후위 표기법 변환 함수
void infixToPostfix(char infix[], char postfix[])
{
  char stack[MAX_STACK];
  int top = -1;
  int i, j;
  char token;

  for (i = 0, j = 0; infix[i] != '\0'; i++)
  {
    token = infix[i];
    if (isalnum(token) || token == '.')
    {
      while (isalnum(infix[i]) || infix[i] == '.' || infix[i] == 'e' || infix[i] == 'E')
      {
        postfix[j++] = infix[i++];
      }
      postfix[j++] = ' ';
      i--;
    }
    else if (token == '(')
    {
      push(stack, &top, token);
    }
    else if (token == ')')
    {
      while (top != -1 && peek(stack, top) != '(')
      {
        postfix[j++] = pop(stack, &top);
        postfix[j++] = ' ';
      }
      if (top != -1 && peek(stack, top) == '(')
      {
        pop(stack, &top);
      }
    }
    else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '^')
    {
      if (token == '-' && (i == 0 || infix[i - 1] == '('))
      {
        if (i + 1 < strlen(infix) && isdigit(infix[i + 1]))
        {
          // -1* 와 같은 형태는 -1로 변환
          postfix[j++] = '-';
          i++; // 다음 토큰으로 이동
          while (isalnum(infix[i]) || infix[i] == '.')
          {
            postfix[j++] = infix[i++];
          }
          postfix[j++] = ' ';
          i--;
        }
        else
        {
          // -(...) 와 같은 형태는 0 - 로 변환
          postfix[j++] = '0';
          postfix[j++] = ' ';
          postfix[j++] = '-';
          postfix[j++] = ' ';
        }
      }
      else
      {
        while (top != -1 && precedence(peek(stack, top)) >= precedence(token))
        {
          postfix[j++] = pop(stack, &top);
          postfix[j++] = ' ';
        }
        push(stack, &top, token);
      }
    }
  }

  while (top != -1)
  {
    postfix[j++] = pop(stack, &top);
    postfix[j++] = ' ';
  }
  postfix[j - 1] = '\0'; // 마지막 공백 제거
}

// 후위 표기법 계산 함수
double evaluatePostfix(char postfix[])
{
  char stack[MAX_STACK][MAX_EXPR];
  int top = -1;
  char *token = strtok(postfix, " ");
  while (token != NULL)
  {
    if (isdigit(token[0]) || token[0] == '.' || token[0] == '-' && isdigit(token[1]))
    {
      strcpy(stack[++top], token);
    }
    else
    {
      double op2 = atof(stack[top--]);
      double op1 = top == -1 ? 0 : atof(stack[top--]);
      double result;
      switch (token[0])
      {
      case '+':
        result = op1 + op2;
        break;
      case '-':
        result = op1 - op2;
        break;
      case '*':
        result = op1 * op2;
        break;
      case '/':
        result = op1 / op2;
        break;
      case '^':
        result = pow(op1, op2);
        break;
      default:
        result = 0;
        break;
      }
      sprintf(stack[++top], "%f", result);
    }
    token = strtok(NULL, " ");
  }
  return atof(stack[top]);
}

int main()
{
  FILE *file = fopen("input.txt", "r");
  if (file == NULL)
  {
    perror("Error opening file");
    return 1;
  }

  int n;
  fscanf(file, "%d\n", &n);

  for (int i = 0; i < n; i++)
  {
    char infix[MAX_EXPR], postfix[MAX_EXPR];
    fgets(infix, MAX_EXPR, file);
    infix[strcspn(infix, "\n")] = 0; // 개행 문자 제거

    infixToPostfix(infix, postfix);

    printf("Infix     : %s\n", infix);
    printf("Postfix   : %s\n", postfix);

    double result = evaluatePostfix(postfix);
    if (fabs(result - (int)result) < 1e-6) // 정수인지 확인
    {
      printf("Result    : %d\n\n", (int)result);
    }
    else
    {
      printf("Result    : %.2f\n\n", result);
    }
  }

  fclose(file);
  return 0;
}

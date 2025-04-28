#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_TERM 1000
#define MAX_LEN 1000

typedef struct
{
    int coef[MAX_TERM]; // 계수를 저장할 배열
} Polynomial;

// 초기화
void init_polynomial(Polynomial *p)
{
    for (int i = 0; i < MAX_TERM; i++)
        p->coef[i] = 0;
}

Polynomial parse(char *str)
{
    Polynomial p;
    init_polynomial(&p);

    char *expr = strdup(str); // 원본 문자열 복사
    int len = strlen(expr);

    // 맨 앞에 '+' 없으면 강제로 붙여줌 (항 파싱을 쉽게 하기 위해)
    if (expr[0] != '+' && expr[0] != '-')
    {
        char *temp = (char *)malloc(len + 2);
        temp[0] = '+';
        strcpy(temp + 1, expr);
        free(expr);
        expr = temp;
        len++;
    }

    // 항 하나씩 추출
    int i = 0;
    while (i < len)
    {
        char sign = expr[i++]; // sign에다가 부호를 저장 후 다음 인덱스로 넘어감
        int start = i;         // 항의 시작 인덱스부터
        while (i < len && expr[i] != '+' && expr[i] != '-')
            i++;
        int end = i; // 항의 끝 인덱스를 저장

        char term[100];
        strncpy(term, expr + start, end - start); // term에 항을 저장
        term[end - start] = '\0';                 // 문자열의 끝임을 명시

        // 항 파싱
        int coef = 0, exp = 0; // coef: 계수, exp: 지수
        int has_coef = 0;      // has_coef: 계수가 있는지 확인하는 변수
        int j = 0;

        // 공백 제거
        while (isspace(term[j]))
            j++;
        // term: +352x**2
        // 계수 숫자 파싱
        while (isdigit(term[j]))
        {
            coef = coef * 10 + (term[j++] - '0'); // 아스키 코드를 이용한 숫자 파싱
            has_coef = 1;
        }

        if (!has_coef)
            coef = 1;
        if (sign == '-')
            coef = -coef;

        if (term[j] == 'x')
        {
            j++;
            if (term[j] == '*' && term[j + 1] == '*')
                j += 2;
            else if (term[j] == '^')
                j++;
            // 지수 숫자 파싱
            if (isdigit(term[j]))
            {
                exp = 0;
                while (isdigit(term[j]))
                {
                    exp = exp * 10 + (term[j++] - '0');
                }
            }
            else
            {
                exp = 1;
            }
        }
        else
        {
            exp = 0;
        }

        p.coef[exp] += coef; // 입력받은 다항식의 계수와 지수를 coef 배열에 coef[지수]=계수로 저장
    }

    free(expr);
    return p;
}

// 덧셈
Polynomial add(Polynomial a, Polynomial b)
{
    Polynomial res;
    init_polynomial(&res);
    for (int i = 0; i < MAX_TERM; i++)
        res.coef[i] = a.coef[i] + b.coef[i];
    return res;
}

// 곱셈
Polynomial multiply(Polynomial a, Polynomial b)
{
    Polynomial res;
    init_polynomial(&res);
    for (int i = 0; i < MAX_TERM; i++)
    {
        if (a.coef[i] == 0)
            continue;
        for (int j = 0; j < MAX_TERM; j++)
        {
            if (b.coef[j] == 0)
                continue;
            res.coef[i + j] += a.coef[i] * b.coef[j];
        }
    }
    return res;
}

// 출력
void print_polynomial(Polynomial p)
{
    int started = 0;
    for (int i = MAX_TERM - 1; i >= 0; i--)
    {
        int coef = p.coef[i];
        if (coef != 0)
        {
            if (started)
            {
                if (coef > 0)
                    printf(" + ");
                else
                    printf(" - ");
            }
            else
            {
                if (coef < 0)
                    printf("-");
            }

            int abs_coef = coef > 0 ? coef : -coef;

            // 계수가 1일 경우 출력 생략 (상수항 제외)
            if (i == 0 || abs_coef != 1)
                printf("%d", abs_coef);
            if (i > 0)
            {
                printf("x");
                if (i > 1)
                    printf("^%d", i);
            }

            started = 1;
        }
    }
    if (!started)
        printf("0");
    printf("\n");
}

int main()
{
    FILE *fp = fopen("input.txt", "r");
    if (!fp)
    {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    char line1[MAX_LEN], line2[MAX_LEN];
    int n;
    fscanf(fp, "%d\n", &n);

    for (int i = 0; i < n; i++)
    {
        fgets(line1, MAX_LEN, fp);
        fgets(line2, MAX_LEN, fp);

        Polynomial p1 = parse(line1);
        Polynomial p2 = parse(line2);

        Polynomial sum = add(p1, p2);
        Polynomial prod = multiply(p1, p2);
        printf("== %d번째 다항식 쌍 ==\n", i + 1);
        printf("첫 번째: ");
        print_polynomial(p1);

        printf("두 번째: ");
        print_polynomial(p2);

        printf("덧셈 결과: ");
        print_polynomial(sum);

        printf("곱셈 결과: ");
        print_polynomial(prod);
        printf("\n");
    }

    fclose(fp);
    return 0;
}

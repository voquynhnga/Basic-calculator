#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define MAX 100
#include <stdbool.h>

void Hi() {
    printf("\n\t******************************************WELCOME*********************************************");
    printf("\n\t*                                                                                           *");
    printf("\n\t*                              PBL 1: DO AN LAP TRINH TINH TOAN                             *");
    printf("\n\t*                              GV huong dan: Tran Ho Thuy Tien                              *");
    printf("\n\t*                                         DE TAI:                                           *");
    printf("\n\t*                 UNG DUNG TINH TOAN BIEU THUC THEO KY PHAP NGHICH DAO BA LAN               *");
    printf("\n\t*                        Thanh vien :                                                       *");
    printf("\n\t*                   Dao Le Hanh Nguyen        102220242   22T_DT5                           *");
    printf("\n\t*                   Vo Thi Quynh Nga          102220241   22T_DT5                           *");
    printf("\n\t*                                                                                           *");
    printf("\n\t******************************************WELCOME*********************************************\n");
}

typedef struct {
    char data1[MAX];
    int top1;
} Stack1;

void Init_1(Stack1 *St1) {
    St1->top1 = -1;
}

int IsFull_1(Stack1 *St1) {
    return St1->top1 == MAX - 1;
}

int IsEmpty_1(Stack1 *St1) {
    return St1->top1 == -1;
}

void Push_1(Stack1 *St1, char x) {
    if (IsFull_1(St1)) {
        printf("\nStack is full!");
        return;
    }
    St1->data1[++St1->top1] = x;
}

char Pop_1(Stack1 *St1) {
    if (IsEmpty_1(St1)) {
        printf("\nStack is empty!");
        exit(EXIT_FAILURE);
    }
    return St1->data1[St1->top1--];
}

char Top(Stack1 *St1) {
    if (IsEmpty_1(St1)) {
        printf("\nStack is empty!");
        exit(EXIT_FAILURE);
    }
    return St1->data1[St1->top1];
}

int Priority(char c) {
    if (c == '+' || c == '-')
        return 1;
    if (c == '*' || c == '/')
        return 2;
    if (c == '^')
        return 3;
    return 0;
}

bool CheckOp(char x) {
    return (x == '+' || x == '-' || x == '*' || x == '/' || x == '^');
}

typedef struct {
    float data2[MAX];
    int top2;
} Stack2;

void Init_2(Stack2 *St2) {
    St2->top2 = -1;
}

int IsFull_2(Stack2 *St2) {
    return St2->top2 == MAX - 1;
}

int IsEmpty_2(Stack2 *St2) {
    return St2->top2 == -1;
}

void Push_2(Stack2 *St2, float x) {
    if (IsFull_2(St2)) {
        printf("\nStack is full!");
        return;
    }
    St2->data2[++St2->top2] = x;
}

float Pop_2(Stack2 *St2) {
    if (IsEmpty_2(St2)) {
        printf("\nStack is empty!");
        exit(EXIT_FAILURE);
    }
    return St2->data2[St2->top2--];
}

float Convertx(const char x[]) {
    return atof(x);
}

void Convert(char *infix, char *postfix) {
    Stack1 St1;
    char x;
    Init_1(&St1);
    int i, j;

    for (i = 0, j = 0; infix[i] != '\0'; i++) {
        x = infix[i];

        if (isalnum(x)) {
            postfix[j++] = infix[i];
            while (isalnum(infix[++i])) {
                postfix[j++] = infix[i];
            }
            i--;
            postfix[j++] = '#';
        } else if (x == '(') {
            Push_1(&St1, x);
        } else if (CheckOp(x)) {
            while (!IsEmpty_1(&St1) && Priority(Top(&St1)) >= Priority(x)) {
                postfix[j++] = Pop_1(&St1);
            }
            Push_1(&St1, x);
        } else if (x == ')') {
            while (!IsEmpty_1(&St1) && Top(&St1) != '(') {
                postfix[j++] = Pop_1(&St1);
            }
            Pop_1(&St1);
        }
    }
    while (!IsEmpty_1(&St1)) {
        postfix[j++] = Pop_1(&St1);
    }
    postfix[j] = '\0';
}

float RPN(char *rpn) {
    Stack2 St2;
    Init_2(&St2);

    float a, b, result = 0;
    char temp[MAX];
    int n = strlen(rpn);

    for (int i = 0; i < n; i++) {
        if (isdigit(rpn[i])) {
            int j = 0;
            while (rpn[i] != '#' && i < n) {
                temp[j++] = rpn[i++];
            }
            temp[j] = '\0';
            Push_2(&St2, Convertx(temp));
        } else if (CheckOp(rpn[i])) {
            b = Pop_2(&St2);
            a = Pop_2(&St2);
            switch (rpn[i]) {
                case '+': result = a + b; break;
                case '-': result = a - b; break;
                case '*': result = a * b; break;
                case '/': result = a / b; break;
                case '^': result = pow(a, b); break;
            }
            Push_2(&St2, result);
        }
    }
    return Pop_2(&St2);
}

int main() {
    char infix[MAX], postfix[MAX];
    char c;

    Hi();
    do {
        printf("\n\nNhap bieu thuc trung to: ");
        fgets(infix, MAX, stdin);
        infix[strcspn(infix, "\n")] = '\0';

        for (int i = 0; i < strlen(infix); i++) {
            if (!isalnum(infix[i]) && !CheckOp(infix[i]) && infix[i] != '(' && infix[i] != ')' && infix[i] != ' ') {
                printf("\nBieu thuc duoc nhap khong hop le!\n");
                goto RESTART;
            }
        }

        Convert(infix, postfix);
        float result = RPN(postfix);
        printf("\nKet qua bieu thuc la: %.3f\n", result);

        RESTART:
        printf("\nNhan 'c' de tiep tuc!\nNhan phim bat ky de thoat!");
        c = getchar();
        while (getchar() != '\n');
    } while (c == 'c');

    return 0;
}

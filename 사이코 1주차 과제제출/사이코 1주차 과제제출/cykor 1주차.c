

#include <stdio.h>
#define STACK_SIZE 50 

int call_stack[STACK_SIZE];
char stack_info[STACK_SIZE][20];

int SP = -1;
int FP = -1;

void push(int value, const char* description) {
    if (SP < STACK_SIZE - 1) {
        SP++;
        call_stack[SP] = value;
        snprintf(stack_info[SP], 20, "%s", description);
    }
}

void pop() {
    if (SP >= 0) {
        printf("Popping: %d : %s = %d\n", SP, stack_info[SP], call_stack[SP]);
        SP--;
    }
}

void print_stack() {
    if (SP == -1) {
        printf("Stack is empty.\n");
        return;
    }

    printf("====== Current Call Stack ======\n");
    for (int i = SP; i >= 0; i--) {
        if (call_stack[i] != -1)
            printf("%d : %s = %d", i, stack_info[i], call_stack[i]);
        else
            printf("%d : %s", i, stack_info[i]);

        if (i == SP)
            printf("    <=== [esp]\n");
        else if (i == FP)
            printf("    <=== [ebp]\n");
        else
            printf("\n");
    }
    printf("================================\n\n");
}

void func3(int arg1) {
    int var_3 = 300;
    int var_4 = 400;

    push(arg1, "arg1");
    push(var_3, "var_3");
    push(var_4, "var_4");

    print_stack();

    pop();
    pop();
    pop();
}

void func2(int arg1, int arg2) {
    int var_2 = 200;

    push(arg1, "arg1");
    push(arg2, "arg2");
    push(var_2, "var_2");

    print_stack();

    func3(77);

    print_stack();

    pop();
    pop();
    pop();
}

void func1(int arg1, int arg2, int arg3) {
    int var_1 = 100;

    push(arg1, "arg1");
    push(arg2, "arg2");
    push(arg3, "arg3");
    push(var_1, "var_1");

    print_stack();

    func2(11, 13);

    print_stack();

    pop();
    pop();
    pop();
    pop();
}

int main() {
    func1(1, 2, 3);

    print_stack();
    return 0;
}
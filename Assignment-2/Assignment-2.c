#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<malloc.h>

#define MAX 10

/*
Q1. Implementation of an Integer-Stack:
In this assignment you are required to implement a stack where integer data can be
pushed and popped. You should define (typedef) an appropriate type called stack such
that multiple variables of type stack can be defined. 
*/

typedef struct {
    int *arr;
    int count;
    int top;
    int capacity;
} stack;

/*
ASSOCIATED FUNCTIONS:

1. intinitIntegerStack(stack s, intstackSize) - This allocates space for the stack to hold
maximum "stackSize" number of integers and initializes that space.

2. intpushIntegerStack(stack s, int d) - It pushes the data d in the stack s. It returns 1 if
the operation is successful. If the operation fails (say, when stack s is full and d cannot
be pushed), the function returns 0.

3. intpopIntegerStack(stack s, int *dp) - It pops from the stack s and stores the popped
element at address dp. It returns 1 if the operation is successful. If the operation fails
(when stack s is empty and popIntegerStack() is attempted), the function returns 0.

4. intfreeIntegerStack(stack s) - It frees the space allocated for stack s. It returns 1 if the
operation is successful. If the operation fails (say, s does not refer to a valid stack), the
function returns 0.

5. intisIntegerStackFull(stack s) - It returns 1 if the stack associated with s is full. The
function returns 0 otherwise. If s does not refer to a valid stack then too the function
returns 1.

6. intisIntegerStackEmpty(stack s) - It returns 1 if the stack associated with s is empty.
The function returns 0 otherwise. If s does not refer to a valid stack then too the
function returns 1.
*/


int initIntegerStack(stack *s, int stackSize) {
    s->capacity =  stackSize;
    s->count=0;
    s->arr = (int *)malloc(stackSize*sizeof(int));
    return 1;
}

int pushIntegerStack(stack *s, int d) {
    if (s->count == s->capacity) {
        printf("Stack is full!\n");
        return 0;
    }
    s->arr[s->count] = d;
    s->count++;
    return 1;
}

int popIntegerStack(stack *s, int *d) {
    if (s->count == 0) {
        printf("Stack is empty!\n");
        return 0;
    }
    *d = s->arr[s->count - 1];  // last element
    s->count--;
    return 1;
}

int freeIntegerStack(stack *s) {
    if (s->arr != NULL) {
        free(s->arr);
        s->arr = NULL;
        s->count = 0;
        s->capacity = 0;
        return 1;
    }
    return 0;
}

int isIntegerStackFull(stack *s) {  //Check if stack is full
    if (s == NULL || s->arr == NULL) return 1;
    return s->count == s->capacity;
}

int isIntegerStackEmpty(stack *s) {  //Check if stack is empty
    if (s == NULL || s->arr == NULL) return 1;
    return s->count == 0;
}


/*
Q2. Using the above Stack implementation, simulate the following:
Assume two stacks are created as stack1 and stack2 of size N and M, respectively. Also,
assume that a series of integers are read from the user and pushed into stack1 first;
if stack1 is full, then push into stack2. This process continues till stack2 is not full.
Once stack2 is full, it should pop all the elements from stack2 and then stack1. Every
time an element is popped should be printed in the console. 
*/

void simulateTwoStacks() {
    int N, M;
    printf("Enter size of stack1: ");
    scanf("%d", &N);
    printf("Enter size of stack2: ");
    scanf("%d", &M);

    stack s1, s2;
    initIntegerStack(&s1, N);
    initIntegerStack(&s2, M);

    int val;
    printf("Enter integers (type -1 to stop):\n");
    while (1) {
        scanf("%d", &val);
        if (val == -1) break;

        if (!isIntegerStackFull(&s1)) {  //if stack s1 not full, can add elements
            pushIntegerStack(&s1, val);
        } 
        else if (!isIntegerStackFull(&s2)) {  //if stack s2 not full, can add elements
            pushIntegerStack(&s2, val);
        } 
        else {
            printf("\nStack2 is full. Now removing elements:\n");
            while (!isIntegerStackEmpty(&s2)) {  //if stack s2 not empty, remove element
                popIntegerStack(&s2, &val);
                printf("%d ", val);
            }
            while (!isIntegerStackEmpty(&s1)) {  //if stack s1 not empty, remove element
                popIntegerStack(&s1, &val);
                printf("%d ", val);
            }
            printf("\n");
        }
    }

  
    printf("\nFinal removing of remaining elements:\n");
    while (!isIntegerStackEmpty(&s2)) {  //if stack s2 not empty, remove element
        popIntegerStack(&s2, &val);
        printf("%d ", val);
    }
    while (!isIntegerStackEmpty(&s1)) {  //if stack s1 not empty, remove element
        popIntegerStack(&s1, &val);
        printf("%d ", val);
    }

    freeIntegerStack(&s1);  //Clear all elements from stack s1
    freeIntegerStack(&s2);  //Clear all elements from stack s2
    printf("\n");
}

/*
Q3. Using the above Stack implementation, check the sanity of a mathematical expression
with different kinds of parenthesis. The application results arecorrect or incorrect based
on the matching parenthesis only.
For example “ { ( A + B ) * C } + D” and “( [ A + B ] - C ) ” are a correct
expression, whereas “ [ ( A + B )”and “( A + B ) } – ( C + D ” are incorrect.
*/


int isMatchingPair(char open, char close) {  //comparing brackets
    return (open == '(' && close == ')') || (open == '{' && close == '}') || (open == '[' && close == ']');
}


/* REFERENCE CODE:
valid = TRUE; //Assume the string is valid 
S = the empty stack;
while (the entire string is not read) {
read the next symbol (symb) of the string;
if (symb == ‘(’ || symb == ‘{’ || symb == ‘[’)
push(S, symb)
if (symb == ‘)’ || symb == ‘}’ || symb == ‘]’)
if empty(S) {
valid = false; break;
Depending upon the value of valid flag, it can be concluded if the parenthesis matched or not.{ ( A + B ) * C } + D1 2 2 2 2 1 1 1 0 0 0valid = false; break;
} else {
elem = pop(S);
if(elem is not matching opener of symb) {
valid = false; break;
} // end if 
} // end else
} // end while 
if ( valid && !empty(S)) {
valid = false;
}
*/

int checkExpression(const char *expr) {
    stack s;
    initIntegerStack(&s, strlen(expr));

    for (int i = 0; expr[i]; i++) {
        char symb = expr[i];
        if (symb == '(' || symb == '{' || symb == '[') {
            pushIntegerStack(&s, symb);
        } else if (symb == ')' || symb == '}' || symb == ']') {
            int top;
            if (!popIntegerStack(&s, &top) || !isMatchingPair(top, symb)) {
                freeIntegerStack(&s);
                return 0;
            }
        }
    }

    int valid = isIntegerStackEmpty(&s);
    freeIntegerStack(&s);
    return valid;
}

void expressionChecker() {
    char expr[100];
    printf("Enter expression to check: ");
    getchar(); 
    fgets(expr, sizeof(expr), stdin);
    expr[strcspn(expr, "\n")] = 0; 

    if (checkExpression(expr)) {
        printf("Expression is correct.\n");
    } else {
        printf("Expression is incorrect.\n");
    }
}

// MAIN
int main() {
    int choice;
    stack s;
    int sc=0; //sc=stack created

    do {
        printf("\n-----------------------------------");
        printf("\n========= Stack Menu (Q1) =========");
        printf("\n-----------------------------------\n");
        printf("1. Space Allocation (init)\n");
        printf("2. Add Elements (push)\n");
        printf("3. Remove Elements (pop)\n");
        printf("4. Clear Stack (free)\n");
        printf("5. Check if Stack is Full\n");
        printf("6. Check if Stack is Empty\n");
        printf("\n-----------------------------------");
        printf("\n========= Stack Menu (Q2) =========");
        printf("\n-----------------------------------\n");
        printf("7. Simulate Two Stacks\n");
        printf("\n-----------------------------------");
        printf("\n========= Stack Menu (Q3) =========");
        printf("\n-----------------------------------\n");
        printf("8. Expression Parenthesis Checker\n");
        printf("\n-----------------------------------\n");
        printf("0. Exit");
        printf("\n-----------------------------------\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int size;
                printf("Enter stack size: ");
                scanf("%d", &size);
                if (!initIntegerStack(&s, size)) {
                    printf("Memory allocation failed!\n");
                } else {
                    sc = 1;
                    printf("Stack initialized with size: %d\n", size);
                }
                break;
            }
            case 2: {
                int val;
                printf("Enter elements to push (type -1 to stop):\n");
                while (1) {
                    scanf("%d", &val);
                    if (val == -1) break;   // stop when user enters -1
                    if (!pushIntegerStack(&s, val)) break; // stop if stack is full
                }
                break;
            }
            case 3: {
                if (!sc) { printf("Stack not initialized!\n"); break; }
                int popped;
                if (popIntegerStack(&s, &popped))
                    printf("Popped: %d\n", popped);
                break;
            }
            case 4: {
                if (!sc) { printf("Stack not initialized!\n"); break; }
                if (freeIntegerStack(&s))
                    printf("Stack cleared.\n");
                sc = 0;
                break;
            }
            case 5: {
                if (isIntegerStackFull(&s))
                    printf("Stack is FULL.\n");
                else
                    printf("Stack is NOT FULL.\n");
                break;
            }
            case 6: {
                if (isIntegerStackEmpty(&s))
                    printf("Stack is EMPTY.\n");
                else
                    printf("Stack is NOT EMPTY.\n");
                break;
            }
            case 7:
                simulateTwoStacks();
                break;
            case 8:
                expressionChecker();
                break;
            case 0:
                printf("Exiting.\n");
                if (sc) freeIntegerStack(&s);
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);

    return 0;
}

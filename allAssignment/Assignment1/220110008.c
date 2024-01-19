#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int top = -1;
char pop(char stack[]);
void push(char x, char stack[]);
int parenthesis(char s[]);
int alphabets(char s[]);
int operators(char s[]);
int prece(char x);


int main(int argc , char *argv[]){
    int lines = 1;
    FILE *fptr;
    FILE *op;
    op = fopen("output.txt", "w");
    int chars=0;
    char x;
    int ops=0;
    int alps=0;
    int bracks=0;
    fptr = fopen(argv[1],"r");
    if (fptr == NULL){
        printf("File doesnt exist");
        return 0;
    }
    while(fscanf(fptr,"%c", &x)!= EOF){
        chars++;
        if(x == '(' || x == ')'){
            bracks++;
        }
        else if((x >= 'a' && x <= 'z') || (x >= 'A' && x <= 'Z')){
            alps++;
        }
        else{
            ops++;
        }
    }
    rewind(fptr);
    char strin[chars];
    int i;
    for(i = 0; i < chars; i++){
        strin[i] = fgetc(fptr);
    }
    strin[i] = '\0';
    if(!parenthesis(strin)){
        fprintf(op, "%s", "Unequal Parenthesis");
        return 0;
    }
    if(!operators(strin) || alphabets(strin)){
        fprintf(op, "%s", "Invalid Expression");   
        return 0;
    }
    char stack[ops];
    char new_str[chars-bracks];
    int j;
    int k= 0;
    for(j = 0; j <= strlen(strin); j++){
        char c = strin[j];
        if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
            new_str[k] = c;
            k++;
        }
        else if (c == '('){
            push(c,stack);
            fprintf(op, "%c is pushed into stack\n", c);
        }
        else if(c == ')'){
            while(stack[top] != '('){

                char u = pop(stack);
                new_str[k] = u;
                k++;
                fprintf(op, "%c is popped from stack\n", u);
            }
            char u = pop(stack);
            fprintf(op, "%c is popped from stack\n", u);
        }
        else if(c == '+' ||c  == '-' || c == '*' || c == '/' || c == '%' || c == '^'){
            if (prece(c) > prece(stack[top]) || stack[top] == '('){
                push(c,stack);
                fprintf(op, "%c is pushed into stack\n", c);
            }
            else if(prece(c) <= prece(stack[top])){
                while(prece(stack[top] >= prece(c)) && stack[top] != '('){
                    char u = pop(stack);
                    new_str[k] = u;
                    k++;
                    fprintf(op, "%c is popped from stack\n", u);
                }
                push(c,stack);
                fprintf(op, "%c is pushed into stack\n", c);

            }

        }
        else{
            while(top != -1){
                char u = pop(stack);
                new_str[k] = u;
                k++;
                fprintf(op, "%c is popped from stack\n", u);
            }
            new_str[k] = '\0';
        }


    }
    fprintf(op, "Postfix expression is %s", new_str);

    return 0;
}

void push(char x, char stack[]){
    top += 1;
    stack[top] = x;
}
char pop(char stack[]){
    top -= 1;
    return stack[top+1];
}

int parenthesis(char s[]){
    int co = 0;
    for(int i = 0; i < strlen(s); i++){
        if(s[i] == '('){
            co += 1;
        }
        else if(s[i] == ')'){
            co -= 1;
        }
        
        if(co < 0){
            return 0;
        }
    }
    if(co == 0){
        return 1;
    }
    else{
        return 0;
    }
}

int alphabets(char s[]){
    for(int j = 0; j < strlen(s)-1; j++){
        if ((s[j] >= 'a' && s[j] <= 'z') || (s[j]>='A' && s[j] <= 'Z')){
            if((s[j+1] >= 'a' && s[j+1] <= 'z') || (s[j]>='A' && s[j+1] <= 'Z') || s[j+1] == '('){
                return 0;
            }
        }
    }
    return 1;
}

int operators(char s[]){
    for(int i = 0; i < strlen(s)-1; i++){
        if(s[i] == '+' ||s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '%' || s[i] == '^'){
            if(s[i+1] == '+' ||s[i+1] == '-' || s[i+1] == '*' || s[i+1] == '/' || s[i+1] == '%' || s[i+1] == '^' || s[i+1] == ')'){
                return 0;
            }
        }
        if(s[i] == ')'){
            if ((s[i+1] >= 'a' && s[i+1] <= 'z') || (s[i+1]>='A' && s[i+1] <= 'Z')){
                return 0;
            }
        }
        if(s[i] == '('){
            if(s[i+1] == '+' ||s[i+1] == '-' || s[i+1] == '*' || s[i+1] == '/' || s[i+1] == '%' || s[i+1] == '^' || s[i+1] == ')'){
            return 0;
            }
        }
    }
    return 1;
}

int prece(char x){
    switch (x)
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
    case '(':
    case ')':
    return 4;
    }
}

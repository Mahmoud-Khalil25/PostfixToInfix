#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int size=100;

typedef union
{
    float fData;
    char  cData;
} Item;
/*
*
*/
typedef struct
{
    int top;
    Item *items;



} Stack;
/*
*
*/
Stack * initialize()
{
    Stack *s=malloc(sizeof(Stack));
    s->items=(Item*)malloc(size*sizeof(Item));
    s->top=0;
    return s;
}
/*
*
*/
int isEmpty(Stack *s)
{
    if(s->top==0)
        return 1;
    else
        return 0;
}
/*
*
*/
Item top(Stack *s)
{
    return s->items[s->top-1];
}
/*
*
*/
Item pop(Stack *s)
{
    return s->items[--s->top];
}
/*
*
*/
void push(Stack *s, Item val)
{
    s->items[s->top++]=val;



}
/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME single-digit operands
* ASSUME ^*+-/ operators
* e.g., 22+31 --> 22 31 +
* e.g., (2+3)*4 --> 2 3 + 4 *
*/
void infixToPostfix(char* infix, char* postfix)
{

    Stack *s=initialize();
    int indexin=0,indexpost=0;
    Item a;

int i;

for(i=0;i<strlen(infix)+1;i++){


    if(infix[indexin]==NULL){


    while(!isEmpty(s)){
       postfix[indexpost]=pop(s).cData;
       indexpost++;
       postfix[indexpost]=' ';
       indexpost++;

    }



}

else if(isdigit(infix[indexin])||infix[indexin]=='.'&& i!=255){


postfix[indexpost]=infix[indexin];
indexpost++;
indexin++;

        }


else if(infix[indexin]==' '){

    if(infix[indexin-1]==' '){
        indexin++;
        continue;}
    else{
    postfix[indexpost]=' ';
    indexpost++;
    indexin++;
    }

}

else if(infix[indexin]=='+'||infix[indexin]=='-'||infix[indexin]=='*'||infix[indexin]=='/'||infix[indexin]=='^'){






 if(infix[indexin]=='-'&&infix[indexin+1]!=' '){

    postfix[indexpost]=infix[indexin];
    indexin++;
    indexpost++;


}
else if(isEmpty(s)){
a.cData=infix[indexin];
push(s,a);
indexin++;
}

else if(top(s).cData=='('){
    a.cData=infix[indexin];
    push(s,a);
    indexin++;
    }

else if(presedence(infix[indexin])==presedence(top(s).cData)){
a.cData=infix[indexin];
while(presedence(infix[indexin])==presedence(top(s).cData)||presedence(infix[indexin])<presedence(top(s).cData)&&!isEmpty(s)){
postfix[indexpost]=pop(s).cData;
postfix[indexpost+1]=' ';
indexpost++;
indexpost++;
}
push(s,a);
indexin++;

}

else if( presedence(infix[indexin])>presedence(top(s).cData) ){
a.cData=infix[indexin];
push(s,a);
indexin++;
}


else if(presedence(infix[indexin])<presedence(top(s).cData)){
a.cData=infix[indexin];
while(presedence(infix[indexin])==presedence(top(s).cData)||presedence(infix[indexin])<presedence(top(s).cData)&&!isEmpty(s)){
postfix[indexpost]=pop(s).cData;
postfix[indexpost+1]=' ';
indexpost++;
indexpost++;
}
push(s,a);
indexin++;
}
} // end of operator else if
else if(infix[indexin]=='('){
a.cData=infix[indexin];
push(s,a);
indexin++;


}

else if(infix[indexin]==')'){
 while(top(s).cData!='('){

     postfix[indexpost]=pop(s).cData;
     indexpost++;



       }


    pop(s);
    indexin++ ;
}





    }



free(s);

}





int presedence(char *c){

if(c=='(')
    return 0;
 else if(c=='+'||c=='-')
    return 1;
else if(c=='*'||c=='/')
    return 2;
 else if(c=='^')
        return 3;
};
//int size_array(char c){
//int i;
//for(i=0;c[0]!='/0')
//i++;

//return i;
//}







/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
* ASSUME single-digit operands
*/

/*
*
*/
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}

int isoperator(char* x){
if(strcmp(x,"^")==0||strcmp(x,"*")==0||strcmp(x,"%")==0||strcmp(x,"/")==0||strcmp(x,"+")==0||strcmp(x,"-")==0)
return 1;
else
return 0;

}
float compute(char* x,float operand1,float operand2){
if(strcmp(x,"+")==0)
return (operand1+operand2);
if(strcmp(x,"-")==0)
return(operand1-operand2);
if(strcmp(x,"*")==0)
return(operand1*operand2);
if(strcmp(x,"/")==0)
return(operand1/operand2);
if(strcmp(x,"^")==0)
return(pow(operand1,operand2));



}

float evaluatePostfix(char* postfix)
{
    /* TODO: ADD YOUR CODE HERE */
    Stack* evaluate=initialize();
    Item a;
     float operand1,operand2,value;
     char *token=strtok(postfix, " ");
    while(token!=NULL){
    if(!isoperator(token)){
    a.fData=atof(token);
    push(evaluate,a);
    }
    else if(isoperator(token)||isdigit(token[1])){
operand2=pop(evaluate).fData;
operand1=pop(evaluate).fData;
value=compute(token,operand1,operand2);
a.fData=value;
push(evaluate,a);



    }


token = strtok(NULL, " ");




}
value=pop(evaluate).fData;

free(evaluate);

    return value;
}


/*
*
*/
int main(int argc, char**argv)
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;





}






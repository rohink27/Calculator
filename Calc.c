#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#define NUMBER 0
int last; // stores last chaaracter sent in getop
enum precedence {OPENING_BRACKET,ADD_MINUS, MULTIPLY_DIVIDE, TRIG, POWER, UNDEFINED};
int get_precedence(int a);
int get_precedence(int a)
{
    if(a=='+'|| a=='-')
    return ADD_MINUS;
    else if(a=='*'|| a=='/')
    return MULTIPLY_DIVIDE;
    else if(a=='s'|| a=='c'||a=='t')
    return TRIG;
    else if(a=='^')
    return POWER;
    else if(a=='(')
    return OPENING_BRACKET;
    else
    return UNDEFINED;
}
#define MAXOP 1000 //stack size
#define MAXVAL 1000 // expression size
int getch();
void ungetch(int a);
void push(int );
int pop();
char expression[MAXVAL];
int sp=0;
char stack[MAXOP];
double stack2[MAXOP];
int sp2=0;
int get_op(char []);

void pushd(double a);
double popd();
void push(int a)
{
    if(sp2<MAXOP)
    stack[sp++]=a;
    else
    printf("Error: stack overflow");
}
int pop()
{
    if(sp>0)
    return stack[--sp];
    else
    {
        printf("Error: stack undeflow");
        return EOF;
    }
}
int get_op(char n[])
{
    int temp;
    while((temp=getch())==' '|| temp=='\t');
    int c= temp;

    if(!isdigit(c)&& c!='-'&& c!='.'){
    last=c;
    return c;
    }
    else if(c=='-' && last== NUMBER)
    {
        last=c;
        return c;
    }
   

        int first =n[0]=c;
        int index=1;
        while(isdigit(c=getch()))
        n[index++]=c;
        if(c=='.'&& first!='.')
        {
            n[index++]=c;
            while(isdigit(c=getch()))
            n[index++]=c;
            ungetch(c);

        }
        else
        ungetch(c);
        n[index]='\0';
        last=NUMBER;
        return NUMBER;
    

}
int main()
{
    
    int c;
    char num[100]; // to store a number
    int expression_index=0;
    while((c=get_op(num))!=EOF)
    {
        if(c==NUMBER)
        {
            int ind=0;
            while(num[ind]!='\0')
            {
                expression[expression_index++]= num[ind++];
            }
            expression[expression_index++]=' ';
        }
        else if(c=='(')
        push(c);
        else if(c==')')
        {
            int t;
            while(sp>0&&(t=pop())!='('){
            expression[expression_index++]=t;
            expression[expression_index++]=' ';
            }

        }
        else if(c=='+'|| c=='-'||c=='*'||c=='/'|| c=='s'||c=='t'||c=='c'||c=='^'|| c=='%')
        {
            int a;
            int flag= (sp>0);
            while(sp>0 && get_precedence((a=pop()))>=get_precedence(c)){
            expression[expression_index++]=a;
            expression[expression_index++]=' ';
            }
            if(flag && get_precedence(a)< get_precedence(c))
            push(a);
            push(c);
        }
        else if(c=='\n')
        {
            int a;
            while(sp>0){
            expression[expression_index++]=pop();
            expression[expression_index++]=' ';
            }
            
            expression[expression_index]='\0';
            printf("%s\n", expression);
            break;
            
            
        }
        else
        {
            printf("Error, unexpected operator");
        }
    }
    int index=0;
    char s[100];
    double op2, op1;
    while(index<=expression_index)
    {
        int x= expression[index];
        
        
        if( x== '-')
        {
            if(expression[index +1]==' ')
            x='-';
            else
            {
                int s_ind=0;
            s[s_ind]=x;
            int incrementer=1;
            while(isdigit(expression[index+incrementer]))
                s[++s_ind]= expression[index+incrementer++];
            if(expression[index+incrementer]=='.')
            {
                s[++s_ind]= expression[index+incrementer++];
                while(isdigit(expression[index+incrementer]))
                s[++s_ind]= expression[index+incrementer++];

            }
                index= index+incrementer-1;
                s[++s_ind]='\0';
                
                
                x=NUMBER+1;

            }
           

        }
        else if(isdigit(x)|| x=='.')
        {
            int s_ind=0;
            s[s_ind]=x;
            int incrementer=1;
            while(isdigit(expression[index+incrementer]))
                s[++s_ind]= expression[index+incrementer++];
            if(expression[index+incrementer]=='.')
            {
                s[++s_ind]= expression[index+incrementer++];
                while(isdigit(expression[index+incrementer]))
                s[++s_ind]= expression[index+incrementer++];

            }
                index= index+incrementer-1;
                s[++s_ind]='\0';
                
                
                x=NUMBER+1;
        }
        if(x==' '){
        index+=1;
        continue;
        }
        
        switch(x)
        {
            case NUMBER+1:
            pushd(atof(s));
            break;
            case '+':
            pushd(popd() + popd());
            break;
            case '*':
            pushd(popd() * popd());
            break;
            case '-':
            op2= popd();
            pushd(popd()- op2); // because in subtraction the order matters
            break;
            case '/':
            op2=popd();
            if(op2!=0)
            pushd(popd()/op2);
            break;
            case '%':
            op2=popd();
            if(op2!=0)
            pushd((int)popd()%(int)op2);
            else
            printf("Error, division by 0\n");
            break;
            case 's':
            pushd(sin(popd()));
            break;
            case 'c':
            pushd(cos(popd()));
            break;
            case 't':
            pushd(tan(popd()));
            break;
            case '^':
            op1= popd();
            pushd(pow(popd(),op1));
            break;
            case '\0':
            // popd and print top of stack
            printf("\t%.8g\n", popd());
            break;
            
            default:
            printf("Unknown Command\n");
        }
        index=index+1;
    }



    return 0;

}
#define BUFSIZE 100
char buf[BUFSIZE];
int bufp=0;
int getch()
{
    return( bufp>0)? buf[--bufp]: getchar(); // first gives unread characters
}
void ungetch(int c)
{
    if(bufp>=BUFSIZE)
    printf("Error,too many unread characters");
    else
    buf[bufp++]=c;
}
void pushd( double f)
{
    if(sp2<MAXVAL)
    stack2[sp2++]=f;
    else
    printf("Stack overflow");

}
double popd(void)
{
    if(sp2>0)
    return stack2[--sp2];
        else
        printf("Stack underflow");
        return 0.0;
    
}


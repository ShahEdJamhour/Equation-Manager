
/*Shahed Jamhour
1180654
section1


*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define isOp(a)((a=='+')||(a=='-')||(a=='/')||(a=='*'))
#define isParnthes(b)((b=='(' ) || (b==')' ) || (b=='[' ) || (b==']' ))
typedef struct node *ptr;
struct node
{
    char data ;
    ptr next;
};

typedef ptr list ;
int kk;
int Error ; // to define error type
//// functions used in this program :
int isValid(char []);
void push(char,list);
char pop(list);
char top(list);
int isempty(list);
char* InfixToPostfix(char *);
char* remove_op(char* );
int Check_Validity(char *);
char* evaluate(char * );
void printError(int  );
int OperationsPrecedence(char);
char* CleanSpaces(char* );
char* ReverseString(char * );
char * ConvertDoubleToString(double );

int menu()
{
    int ch;

    printf("\n\t\t_____________________________Equation Manager_________________________________\n") ;
    printf("  Press:\n");
    printf("\n1) To read file");
    printf("\n2) Check if equations are Valid or not");
    printf("\n3) Print the postfix expressions");
    printf("\n4) Evaluate the postfix expressions and print the results");
    printf("\n5) Print invalid equations");
    printf("\n6) Print equations on file and state if they are valid or not , if valid print postfix and results\n \n");
    printf("\n7) Exit\n");
    printf("\t\t_________________________________________________________________________________\n");
    scanf("%d",&ch);
    printf("\n\n");
    return ch;
}
int main()
{
    FILE *input,*output ;
    char equ[50][50];
    char equ2[50][50];
    char infix[50][50];
    char postfix [50][50];
    char invalid[50][50];
    char line[50];
    float result[50];
    int NumOfEq =0 ; // to count the number of equations
    int k=0 ; // to count invalid
    int j=0 ; // to count infix

    int Step1=0,Step2=0,Step3=0,Step4=0,Step5=0;
    int choice;
    system("cls"); // to clear screen
    while(1)
    {
        choice = menu();
        switch(choice)
        {
        case 1 :
        {
            // Reading from file
            char file_name[20];
            printf("Enter name of file\n\n");
            scanf("%s", file_name);
            sprintf(file_name,"%s.txt",file_name);
            input = fopen(file_name,"r");
            char *s=fgets(line,50,input);

            while(s!= '\0')  // not end of line
            {
                Unify_Parenthesis(line);
                s[strlen(s)-1]='\0';
                strcpy(equ[NumOfEq],s);
                remove_op(equ[NumOfEq]);
                NumOfEq++;

                if(isValid(s)==1) // get infix if valid
                {
                    strcpy(infix[j],s);
                    remove_op(infix[j]);
                    j++;
                }
                else
                {
                    strcpy(invalid[k],s);

                    k++;
                }
                s=fgets(line,50,input);
            }


            fclose(input);
            printf("\n \t***Done Reading***\n\n");
            Step1=1;
            break;
        }

        // state if valid or not
        case 2 :
        {
            if(Step1==0)
            {
                printf("Pls make sure to check step 1 \n");
                break;
            }
            int count;
            for(count=0 ; count < NumOfEq ; ++ count)
            {
                if(isValid(equ[count])== 1)
                    printf(" Equation number %d -> valid\n",count,equ[count]);
                else

                    printf("Equation number %d  -> invalid >>>  ",count,equ[count]);

                printError(getErrorType());
                printf ("\n");
            }
            Step2 = 1 ;
            break;
        }
// infix to postfix
        case 3 :
        {
            if( Step1 == 0 || Step2 ==0)
            {
                if(Step1==0)
                    printf("Check step  1 first  \n");
                if(Step2==0)
                    printf("Check step  2 first  \n");
                break ;
            }
            int c;
            printf("Postfix expression: : \n\n");

            for(c=0; c<j; c++)
            {
                strcpy(postfix[c],InfixToPostfix(infix[c]));
                printf("  %s\n",postfix[c]);
            }
            Step3 = 1;
            break;
        }
        case 4 :
        {
            if( Step1 == 0 || Step2 ==0 || Step3 ==0)
            {
                if(Step1==0)
                    printf("Check step  1 first  \n");
                if(Step2==0)
                    printf("Check step  2 first \n");
                if(Step3==0)
                    printf("Check step  3 first  \n");
                break ;
            }
            int c;
            printf(" Results :\n\n");
            for(c=0; c<j; c++)
            {
                printf("  %d. %-30s",c+1,infix[c]); // print the infix
                strcpy(postfix[c],InfixToPostfix(infix[c]));  // calling the infix to postfix function
                if(strcmp(evaluate(postfix[c]),"infinity")==0)  // by 0
                    printf("infinity\n");
                else
                {
                    result[c]=atof(ReverseString(evaluate(postfix[c]))); // atof is used to convert to string to float
                    printf(" = %.3f\n",result[c]);
                }
            }


            Step4 = 1 ;
            break;
        }

//print invalid
        case 5 :
        {
            int Counter;
            printf(" The following Equations are Invalid :  \n");
            for(Counter=0 ; Counter < NumOfEq ; ++ Counter) //while counter is less than number of equations
            {
                if(isValid(equ[Counter])== 0)
                    printf("  %s \n",equ[Counter]);  //print invalid
            }
            break;
        }

        // print on file
        case 6:
        {


            if( Step1 == 0 || Step2 ==0 || Step3 ==0 || Step4 ==0)
            {
                if(Step1==0)
                    printf("Check step 1\n");
                if(Step2==0)
                    printf("Check step  2 first  \n");
                if(Step3==0)
                    printf("Check step  3 first\n");
                if(Step4==0)
                    printf("Check step  4 first \n");

                break ;
            }
            output = fopen("output.txt","w");
            int c;
            int EqC;

            // to print the equations
            for(EqC=0 ; EqC < NumOfEq ; ++ EqC)
            {

                if(isValid(equ[EqC])== 1)
                    fprintf(output," Equation number (%d)  %s  -> valid\n",EqC,equ[EqC]);
                else

                    fprintf(output,"Equation number (%d) %s  -> invalid \n  ",EqC,equ[EqC]);
                //   printError(getErrorType());
            }

            fprintf(output," ______________________________________________________\n\n");

            // to print the postfix and result
            fprintf(output," Postfix and Result:  ");
            for(c=0; c<j; ++c)
            {

                fprintf(output,"{%s}==>{%s}==>{%.1f}\n",infix[c],postfix[c],result[c]);  // print infix , postfix and result for valid equations


            }



            printf("Done :)");
            fclose(output);
            break ;
        }
        case 7 :
        {
            exit(0);
        }
        default :
        {
            printf("\nPlease Enter a value from the menu\n");
            break ;
        }

        }

    }
    return 0;
}



// Remove spaces
char* CleanSpaces(char* str)
{
    char *t=str;
    int i;
    int v;
    for (i = 0,v = 0; i<strlen(str); i++,v++)
    {
        if (str[i] != ' ')//Not a space
            t[v]=str[i];
        else
            v--;
    }
    t[v]='\0';
    return t;
}
/////////////////////////////////////////////////////////////////////////////////////////////////



//This method convert infix equation to postfix
char * InfixToPostfix(char *c)
{
    list s;
    s=(list)malloc(sizeof(struct node));
    s->next=NULL;
    char Postfix_expression[100]="";
    int j=0;
    int i=0;
    char x;


    if(c[0]=='-')
    {
        Postfix_expression[j]=c[0]; //store '-' in the postfix
        j++;
        i++;
    }
    while(c[i]!='\0') //loop until the end of the infix expression c
    {
        if(isdigit(c[i]) || c[i]=='.') //if the character is digit (0-9) or '.'
        {
            Postfix_expression[j]=c[i];//store the character in postfix expression
            j++;
            if(!isdigit(c[i+1]) && c[i+1]!='.')
            {
                Postfix_expression[j]=' '; //put space between each two numbers
                j++;
            }
        }
        else if(c[i] == '(')
            push('(',s);
        else
        {
            if(c[i] == ')')
            {
                //if c[i]==')' pop until reach '('
                while((x=pop(s))!='(')
                    Postfix_expression[j]=x;//store the popped element(operations) in the postfix expression
                j++;
                Postfix_expression[j]=' ';//put space between each 2 operations( popped )
                j++;
            }
            else //When c[i] is an operation('-','+','/','*')
            {
                //check the precede of top of the stack and c[i]
                while(OperationsPrecedence(c[i])<= OperationsPrecedence(top(s)) && !isempty(s)) //if c[i] has less percede than top of the stack
                {
                    x=pop(s);
                    Postfix_expression[j]=x; //store the popped element in the postfix expression
                    j++;
                    Postfix_expression[j]=' ';//store space between each 2 operations
                    j++;
                }
                push(c[i],s);//push c[i] in the stack
            }
        }
        i++;
    }
    //when we reach end of infix equation and the stack is not empty first
    while(!isempty(s))
    {
        x=pop(s);//pop the stack
        Postfix_expression[j]=x;//store the popped element in the postfix equation
        j++;
        Postfix_expression[j]=' '; //store space between each 2 operations
        j++;
    }
    c=Postfix_expression;
    return c;
}




//This function to convert (-- to +) AND remove + (when - comes after +)
char* remove_op(char* str)
{
    char *oper=str;
      int k;
    int i;
    int j;

    for (i = 0,j = 0; i<strlen(str); i++,j++)
    {
        if (str[i] != '-' || str[i+1]!='-')
            oper[j]=str[i];
        else
        {
            oper[j]='+';
            i++;
        }
    }
    oper[j]='\0';
    for (i = 0,j = 0; i<strlen(str); i++,j++)
    {
        if (str[i] != '+' || str[i+1]!='-')
            oper[j]=str[i];
        else
        {
            k=i;
            while(k<strlen(str))
            {
                oper[j]=str[i+1];
                k++;
            }
            i++;
        }
    }
    while(j<strlen(str))
    {
        oper[j]='\0';
        j++;
    }
    return oper;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////
// check the Precedence of an operation
int OperationsPrecedence(char x)
{
    if(x == '(' || x=='[')
        return(0);

    if(x == '+' || x == '-')
        return(1);
    if(x == '*' || x == '/' || x == '%')
        return(2);
    if(x == '^')
        return 3;
    return(4);
}
///////////////////////////////////

int isOperand(char s)
{
    if (s =='+' || s == '-' || s == '*' || s =='/' || s == '^'  )
        return 1;
    else if(s== ')' || s=='(')
        return 2;
    else
        return 0;
}
//////////////////////////////////////////////////////////////////////////////////////
//This method check if the stack is empty or not
int isempty(list s)
{
    return (s->next==NULL);
}
///////////////////////////////////////////////////////////////////////////////


// return the top element in the stack
char top(list l)
{
    if(isempty(l))
        return '\0';
    else
        return l->next->data;
}



// pop character from stack
char pop(list l)
{

    list temp;
    char d;
    if(l->next==NULL)//empty stack
        return '\0';
    else
    {
        //delete the first node after the head
        temp=l->next;
        d=temp->data;
        l->next=temp->next;
        free(temp);
    }
    return d;
}
////////////////////////////////////////////////////////////////////////
// push a character in the stack
void push(char x,list l)
{
    list temp;
    if(l==NULL)
    {
        l=(list)malloc(sizeof(struct node));
        l->next=NULL;
    }
    temp=(list)malloc(sizeof(struct node));//create new node
    if(temp !=NULL)
    {
        temp->data=x;
        //add the node after header
        temp->next=l->next;
        l->next=temp;
    }
}
///////////////////////////////////////////////////////////////////////
// to reverse string
char * ReverseString(char * a)
{
    int i;
    char temp;
    for(i=0; i<strlen(a)/2; i++)
    {
        temp=a[i];
        a[i]=a[strlen(a)-i-1];
        a[strlen(a)-1]=temp;
    }
    return a;
}
////////////////////////////////////////////////////////////
//evaluate postfix expression
char* evaluate(char *c )
{
    list s;
    s=(list)malloc(sizeof(struct node));
    s->next=NULL;
    int i=0;
    int j=0;
    char x;  //represent the popped character
    char operand1[20]="";
    char operand2[20]="";
    char a[10]="";
    double d;
    static char result[20]="";
    if(c[0]=='-')
    {
        push(c[0],s);
        i++;
    }
    while(c[i] !='\0')
    {
        if(isdigit(c[i]))//if c[i] is between(0-9) or '.'
        {
            push(c[i],s);
            if(c[i+1]==' ') //The end of the number
                push(' ',s);
        }
        else
        {
            if(c[i] != ' ')//don't push the space
            {
                j=0;
                x=pop(s);
                if(x==' ')
                    x=pop(s);
                while(x != ' ' && x !='\0')//pop until reach end of operand1 which is ' ' or '\0'
                {
                    operand1[j]=x;
                    j++;
                    x=pop(s);
                }
                operand1[j]='\0';
                j=0;
                x=pop(s);
                if(x==' ')
                    x=pop(s);
                while(x != ' '&& x !='\0')//pop until reach end of operand2 which is ' ' or '\0'
                {
                    operand2[j]=x;
                    j++;
                    x=pop(s);
                }
                operand2[j]='\0';
                if(c[i]=='+')
                {
                    d=atof(ReverseString(operand2))+atof(ReverseString(operand1));//compute the result of addition
                    strcpy(a,ConvertDoubleToString(d));//convert the result to string
                    push(' ',s);
                    //push the result to the stack
                    for(j=0; j<strlen(a); j++)
                        push(a[j],s);
                    push(' ',s);
                }
                else if(c[i]=='-')
                {
                    d=atof(ReverseString(operand2))-atof(ReverseString(operand1));//compute the result of subtraction
                    strcpy(a,ConvertDoubleToString(d));//convert the result to string
                    push(' ',s);
                    //push the result to the stack
                    for(j=0; j<strlen(a); j++)
                        push(a[j],s);
                    push(' ',s);
                }
                else if(c[i]=='*')
                {
                    d=atof(ReverseString(operand2))*atof(ReverseString(operand1));//compute the result of multiplication
                    strcpy(a,ConvertDoubleToString(d));//convert the result to string
                    push(' ',s);
                    //push the result to the stack
                    for(j=0; j<strlen(a); j++)
                        push(a[j],s);
                    push(' ',s);
                }
                else if(c[i]=='/')
                {
                    d=atof(ReverseString(operand2))/atof(ReverseString(operand1));//compute the result of division
                    strcpy(a,ConvertDoubleToString(d));//convert the result to string
                    push(' ',s);
                    //push the result to the stack
                    for(j=0; j<strlen(a); j++)
                        push(a[j],s);
                    push(' ',s);
                }
            }
        }
        i++;
    }
    j=0;
    //pop the result
    x=pop(s);
    if(x==' ')
        x=pop(s);
    while(x != ' ' && x !='\0')
    {
        result[j]=x;
        j++;
        x=pop(s);
    }
    result[j]='\0';
    for(j=0; j<strlen(result); j++)
        if(!isdigit(result[j]) && result[j] !='.' && result[j] !='-')
        {
            strcpy(result,"infinity");
            result[strlen(result)]='\0';
            break;
        }
    return result;
}
/////////////////////////////////////////////////////////////////////////////////////

//This method is to convert a double to string
char * ConvertDoubleToString(double num)
{
    double num1;//Represent the fraction part of double number
    int num2;//Represent the integer part of double number
    char x;
    int i=0;
    int j=0;
    char c[10]="";
    static char s[10]="";
    num1 = num -(int)num;
    if(num<0)
        num1=-1*num1;
    num2 = abs((int)num);
    while (num2 != 0)
    {
        x=(num2% 10+'0');
        num2 /= 10;
        c[i]=x;
        i++;
    }
    if (num < 0)  // check for negative value
    {
        c[i]='-';
        i++;
    }
    strcpy(s,ReverseString(c));//ReverseString num2
    s[i]='\0';
    if (num1 != 0)//there is a fraction part
    {
        c[j]='.';
        j++;
    }
    while (num1 != 0 && j<5)
    {
        num1 *= 10;
        c[j]=num1+'0';
        j++;
        num1=num1-(int)num1;
    }
    c[j] = '\0';
    return strcat(s,c);
}


// To unify parenthesis
void Unify_Parenthesis(char a[])
{
    int i ;
    for(i=0; i<strlen(a); i++)
    {
        if(a[i] == '[' || a[i]=='{')
            a[i] = '(';
        else if (a[i] ==']' || a[i]=='{')
            a[i] = ')' ;
    }

}


int isValid(char eq[])
{
    kk =0 ;
    int i ;
//////////////////
// brackets errors
    int p1=0 ;
    for(i=0 ; eq[i] != 0; i++)
    {
        if (eq[i]=='(') p1++ ;
        else if(eq[i]==')') p1-- ;
        if(p1<0)
        {
            kk =1 ;        // missing (
            return 0 ;
        }
    }
    if(p1 != 0 )
    {
        kk=2 ;       // missing )
        return 0 ;
    }

/////////////////
// start with op
    if(isOp(eq[0]))
    {
        if(eq[0]!='-')
        {
            kk =3 ;      // start with op
            return 0 ;
        }
        else if(eq[1] == '-')
        {
            kk=3 ;
            return 0 ;
        }
    }
//////////////////
//end with op
    if(isOp(eq[strlen(eq)-1]))
    {
        kk =4 ;             // end with op
        return 0 ;
    }
/////////////////////////




    // three op
    for(i=0; i<strlen(eq); i++)
        if(isOp(eq[i]))
        {
            if(isOp(eq[i-1]) && isOp(eq[i+1]))
            {
                return 0 ;
                kk=11;

            }
        }

///// before and after brackets
    for (i=0 ; i<strlen(eq); i++)
    {
        if(eq[i]=='(')
        {
            if(isOp(eq[i+1]))
                if(eq[i+1]!='-')
                {
                    kk = 5 ;   // operation after [ , (  missing data
                    return 0 ;
                }

            if(i!=0 && isdigit(eq[i-1]))
            {
                kk = 6 ;         // number beftor (     missing operations
                return 0 ;
            }

        }

        if(eq[i] == ')' )
        {
            if(isOp(eq[i-1]))
            {
                kk = 7 ;             // operation before )
                return 0 ;
            }

            if(eq[i+1]!=0 && isdigit(eq[i+1]))
            {
                kk= 8;                // number after  )
                return  0 ;
            }
        }


    }

/////////////////////////
    for(i=0; i<strlen(eq); i++)
        if(isOp(eq[i]))
        {
            if(isOp(eq[i+1]))
            {
                if(eq[i+1] =='-' && isdigit(eq[i+2]))
                {
                    i+=2 ;
                    continue ;
                }
                kk = 9 ;                   // tow operation after each others
                return 0 ;
            }
            i++;
        }
//////////////////////////
// no data between brackets
    for (i=0 ; i<strlen(eq) ; i++)
    {
        if(eq[i]=='(' && eq[i+1] == ')')
        {
            kk = 10 ;
            return 0 ;     // empty brackets
        }
    }

/////////////////////////////
    return 1 ;
}

///print error of invalid equations
void printError(int kk )
{

    if(kk ==1) printf("\nMissing ( or [ !!\n");
    else if(kk==2) printf("  Missing )  !!\n ");
    else if(kk==3) printf("equation start with operation ");
    else if(kk==4) printf("equation end with operation ");
    else if(kk==5) printf("missing data after (  ");
    else if(kk==6) printf("missing operation before (  ");
    else if(kk==7) printf("missing data before )  ");
    else if(kk==8) printf("missing operation after )  ");
    else if(kk==9) printf("missing data between operations ");
    else if(kk==10)printf("missing data between brackets ");
    else if(kk==11)printf("Three operations ");

}

int getErrorType()
{
    return kk ;
}

int isEquation(char s[])
{
    if(strlen(s)==0)
        return 0 ;

    int i =0 ;
    for(i =0 ; i<strlen(s) ; i++)
    {
        if(!isdigit(s[i]) )
            if(!isOp(s[i]))
                if(!isParnthes(s[i]))
                    return 0 ;
    }
    return 1 ;
}




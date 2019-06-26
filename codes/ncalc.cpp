#include <iostream>
#include "ChrStack.h"
#include "IntStack.h"
#include "infix.h"
#include <fstream>
#include <string>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <math.h>

using namespace std;
int getWeight(char ch) {//for operator precedence
   switch (ch) {
      case '^': return 3;
      case '/':
      case '*': return 2;
      case '+':
      case '-': return 1;
      default : return 0;
   }
}
int isOperator(char character)
{
if (character == '+' || character == '-' || character == '*' || character == '/' || character=='^') {
return 1;
}
return 0;
}
int isOperand(char character)
{
if (isOperator(character) == 0 && character != '(' && character != ')') {
return 1;
}
return 0;
}

int isp(char op) {
switch(op)
{
case '+':
case '-':
return 1;
break;
case '*':
case '/':
return 3;
break;
case '^':
return 6;
break;
return 0;
break;
}
}

int icp(char op) {
switch(op)
{
case '+':
case '-':
return 2;
break;
case '*':
case '/':
return 4;
break;
case '^':
return 5;
break;
return 0;
break;
}
}
void reverse(char* str, int len) 
{
for(int i=0; i<len/2; i++) 
{
char temp=str[i];
str[i]=str[len-i-1];
str[len-i-1]=temp;
}
}
void infix2prefix(char *inf,ostream& stream){
ChrStack s(100);
char pre[100], tmp[100], *ptr;
reverse(inf, strlen(inf));
strcpy(tmp, "");
strcpy(pre, " ");
ptr = inf;
while(*ptr!='\0')
{
	if(isOperand(*ptr))
	{
		sprintf(tmp, "%c", *ptr);

		if(isOperand(*(ptr+1)))
		{
		strcat(pre, tmp);
		}
		else
		{
		strcat(pre, tmp);
		strcat(pre," ");
		}
	}
	else if(isOperator(*ptr))
	{
		while(s.empty() && s.getlast()!=')' && isp(s.getlast())>icp(*ptr))
		{
			sprintf(tmp, "%c", s.pop());

			strcat(pre, tmp);
			strcat(pre," ");
		}
		s.push(*ptr);
	}
	else if(*ptr==')')
	{
		s.push(*ptr);
	}
	else if(*ptr=='(')
	{
		while(s.empty())
		{
			if(s.getlast()==')')
			{
				s.pop();
				break;
			}	
			if(s.getlast()=='(')
			{
			continue;
			}
			sprintf(tmp, "%c", s.pop());

			strcat(pre, tmp);
			strcat(pre," ");
		}
	}
	*ptr++;
}
while(s.empty())
{
	sprintf(tmp, "%c", s.getlast());
	strcat(pre, tmp);
	strcat(pre," ");
	s.pop();
}
reverse(pre, strlen(pre));

stream<<pre<<endl;

}
void infix2postfix(char infix[], char postfix[], int size) {
   ChrStack s(50);
   int weight;
   int weight2;
   int i = 0;
   int k = 0;
   char ch;
   // iterate over the infix expression   
   while (i < size) {
	  
      ch = infix[i];
      if (ch == '(') {
         // simply push the opening parenthesis
         s.push(ch);
         i++;
         continue;
      }
      if (ch == ')') {
         // if we see a closing parenthesis,
         // pop of all the elements and append it to
         // the postfix expression till we encounter
         // a opening parenthesis
         while (!s.empty() && s.getlast() != '(') {
            postfix[k++] = ' ';
            postfix[k++] = s.getlast();
            s.pop();

         }
         // pop off the opening parenthesis also
         if (!s.empty()) {
            s.pop();
         }
         i++;
         continue;
      }
      weight = getWeight(ch);
      if (weight == 0) {
         // we saw an operand
         // simply append it to postfix expression
         weight2=getWeight(infix[i+1]);
         if(weight2==0){
             postfix[k++] = ch;
         }else{
             
             
             postfix[k++] = ch;
             postfix[k++] = ' ';
         }
         
         

      }
      else {
         // we saw an operator
         if (!s.empty()) {
            // simply push the operator onto stack if
            // stack is empty
            s.push(ch);
			
         }
         else {
            // pop of all the operators from the stack and
            // append it to the postfix expression till we
            // see an operator with a lower precedence that
            // the current operator
            while (s.empty() && s.getlast() != '(' &&
                  weight <= getWeight(s.getlast())) {
					  
						postfix[k++] = ' ';
						postfix[k++] = s.getlast();
						s.pop();

            }
            // push the current operator onto stack
            s.push(ch);
         }
      }
      i++;
   }
   // pop of the remaining operators present in the stack
   // and append it to postfix expression 
   while (s.empty()) {
	   if(s.getlast()!='('){
       postfix[k++] = ' ';
      postfix[k++] = s.getlast();
	 }
       s.pop();
   }
   
   postfix[k] = 0; // null terminate the postfix expression 
}
int bracket_calculator(char * operators,int size) {
    int count=0;
    for(int i=0; i<size; i++)
    {
        if(operators[size-i-1]=='+'||operators[size-i-1]=='-') {
            if(operators[size-i-2]=='*'||operators[size-i-2]=='/'||operators[size-i-2]=='^') {

                count++;
            }
        }
        if(operators[size-i-1]=='*'||operators[size-i-1]=='/'||operators[size-i-1]=='^') {
            if(operators[size-i-2]=='*'||operators[size-i-2]=='/'||operators[size-i-2]=='^') {

                count++;
            }
        }
		if(operators[size-i-1]=='+'){
			if(operators[size-i-2]=='-'){
				count++;
			}
		}
    }
    return count;
}

int numDigits(int number)
{
    int digits = 0;
    while (number) {
        number /= 10;
        digits++;
    }
    return digits;
}

void set(char commands[5][100], int line_number,char result[5][200])

{
	

    for (int i = 0; i < line_number; i++) {

		IntStack intstack(100);
		ChrStack charstack(100);
		


        char* pch;

        char* chars;

        char* infix=new char[200];

		int indice=199;

        pch = strtok(commands[i], " ");



        while (pch != NULL) {



            if (pch[0] == '+' || pch[0] == '-' || pch[0] == '*' || pch[0] == '/' || pch[0] == '^') {

                charstack.push(pch[0]);

            }

            else

            {

                int a = atoi(pch);
                intstack.push(a);

            }


            pch = strtok(NULL, " ");

        }
        chars=charstack.getstack();





        if ((intstack.getTop() - charstack.getTop()) == 1) {
            
            int numofbracket=bracket_calculator(charstack.getstack(),charstack.getTop());

            for(int t=0; t<numofbracket; t++) {
                infix[indice]=')';
                indice--;
            }
			
            int checker=0;
            while(charstack.getTop()!=0) {
                int bracket=0;
                char x1=charstack.pop();
                char x2=charstack.getlast();
                int op1=intstack.pop();
                int op2=intstack.getlast();
                int dg1=numDigits(op1);
                int dg2=numDigits(op2);
                
                if(x1=='+'||x1=='-') {

                    if(x2=='/'||x2=='*'||x2=='^') {

                        bracket=1;


                    }
                }
                if(x1=='*'||x1=='/'||x1=='^') {
                    if(x2=='*'||x2=='/'||x2=='^') {
                        bracket=1;
                    }
                }
				if(x1=='+'){
					if(x2=='-'){
						bracket=1;
					}
				}
				

                if(checker==0) {
                    if(dg1<2&&dg2<2) {
                        char temp1[2],temp2[2];
                        sprintf(temp1,"%d",op1);
                        sprintf(temp2,"%d",op2);
                        infix[indice]=temp1[0];
                        indice--;
                        infix[indice]=x1;
                        indice--;
                        infix[indice]=temp2[0];
                        indice--;
                    } else {
                        char temp1[10],temp2[10];
                        sprintf(temp1, "%d", op1);
                        sprintf(temp2,"%d",op2);

                        for(int k=0; k<dg1; k++) {
                            infix[indice]=temp1[dg1-k-1];
                            indice--;
                        }
                        infix[indice]=x1;
                        indice--;
                        for(int k=0; k<dg2; k++) {
                            infix[indice]=temp2[dg2-k-1];
                            indice--;
                        }

                    }

                    checker=1;

                } else {
                    if(dg2<2) {
                        char temp[2];
                        sprintf(temp,"%d",op2);
                        infix[indice]=x1;
                        indice--;
                        infix[indice]=temp[0];
                        indice--;
                    } else {
                        char temp[10];
                        sprintf(temp,"%d",op2);
                        infix[indice]=x1;
                        indice--;
                        for(int k=0; k<dg2; k++) {
                            infix[indice]=temp[dg2-k-1];
                            indice--;
                        }

                    }
                }


                if(bracket==1) {

                    infix[indice]='(';
                    indice--;
                }

            }

        }
		int indice2=0;
		
		
        for (; indice<200; indice++) {
			result[i][indice2-1]=infix[indice];
			indice2++;
				
        }
		
		result[i][indice2-1]='\0';
       
        free(infix);

    }
	

}



int read(char* arrg, char commands[5][100])

{

    string str;

    ifstream file(arrg);

    int index = 0;



    while (getline(file, str)) {

        strcpy(*(commands + index), str.c_str());

        index++;

    }

    file.close();

    return index;

}

int calculator(char commands[5][100],int size,char *file){
	ofstream outfile;
	outfile.open(file);
	for(int i=0;i<size;i++){
		ChrStack charstack(100);
		IntStack intstack(100);
		char* pch;
		int NaN=0;
		pch = strtok(commands[i], " ");
		while (pch != NULL) {//push all to stacks
            if (pch[0] == '+' || pch[0] == '-' || pch[0] == '*' || pch[0] == '/' || pch[0] == '^')
			{
                charstack.push(pch[0]);
            }
            else
            {
                int a = atoi(pch);
                intstack.push(a);
            }
            pch = strtok(NULL, " ");
        }
		while(charstack.getTop()!=0){//calculate the expressions
			char ch=charstack.pop();
			int op2=intstack.pop();
			int op1=intstack.pop();
			if(ch=='+')
			{
				intstack.push(op1+op2);
			}
			if(ch=='-')
			{
				intstack.push(op1-op2);
			}
			if(ch=='*')
			{
				intstack.push(op1*op2);
			}
			if(ch=='^'){
				intstack.push(pow(op1,op2));
			}
			if(ch=='/')
			{
				if(op2==0){
					NaN=1;
				}
				else
				{
					intstack.push(op1/op2);
				}
			}
		}
		if(NaN==1)
		{
			outfile << "NaN" << endl;
			
			
		}
		else
		{
			outfile<< intstack.getlast() << endl;
			
		}
	}
	return 0;
}
int main(int argc, char* argv[])
{
    char commands[5][100];//lines in input file
	char commands2[5][100];

    int line_number = 0;

    ofstream outfile2, outfile3,outfile1;;
	outfile1.open(argv[2]);
    outfile2.open(argv[3]);
    outfile3.open(argv[4]);
	
    line_number = read(argv[1], commands);
	read(argv[1], commands2);//reading second times for calculating result.
	char infix_expressions[line_number][200];
	char postfix_expressions[line_number][200];
	calculator(commands2,line_number,argv[5]);
    set(commands, line_number,infix_expressions);
	for(int i=0;i<line_number;i++){
		
		int size=strlen(infix_expressions[i]);
		infix2postfix(infix_expressions[i],postfix_expressions[i],size);
		outfile2 << infix_expressions[i] << endl;
		outfile3 << postfix_expressions[i] << endl;
		infix2prefix(infix_expressions[i],outfile1);

	}
	outfile1.close();
	outfile2.close();
	outfile3.close();
	

    return 0;

}
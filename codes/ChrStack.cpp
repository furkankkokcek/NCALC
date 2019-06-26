#include "ChrStack.h"

ChrStack::ChrStack(int num)
  {
        top = 0;
        maxelem = num;
        s = new char[maxelem];
    }
	
    void ChrStack::push(char t)
    {
        if (top == maxelem)
            return;
        s[top++] = t;
    }

    char ChrStack::pop()
    {
        if (top == 0)
            return 'f';
        return s[--top];
    }
    char ChrStack::getlast()
    {
        if (top == 0)
            return 'f';
        return s[top-1];
    }

    void ChrStack::setTop()
    {
        top == 0;
    }

    int ChrStack::getTop()
    {
        return top;
    }
	
    char* ChrStack::getstack() 
	{
        return this->s;
    }
	int ChrStack::empty()
	{
		if(top==0)
{
			return 0;
		}
		return 1;
	}
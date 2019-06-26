#include "IntStack.h"

  IntStack::IntStack(int num)
    {
        top = 0;
        maxelem = num;
        s = new int[maxelem];
    }
	
    void IntStack::push(int t)
    {
        if (top == maxelem)
            return;
        s[top++] = t;
    }

    int IntStack::pop()
    {
        if (top == 0)
            return -1;
        return s[--top];
    }
	
    void IntStack::setTop()
    {
        top == 0;
    }

    int IntStack::getTop()
    {
        return top;
    }
	
    int IntStack::getlast()
    {
        if (top == 0)
            return -1;
        return s[top-1];
    }
#include <iostream>
#include <fstream>
#include <string>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <cstring>

using namespace std;
class IntStack{

private:
	int* s;
    int top;
    int maxelem;
public:
    IntStack(int);
	void push(int);
	int pop();
	int getlast();
	void setTop();
	int getTop();
};
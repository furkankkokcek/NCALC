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
class ChrStack{

private:
	char* s;
    int top;
    int maxelem;
public:
    ChrStack(int);
	void push(char);
	char pop();
	char getlast();
	void setTop();
	int getTop();
	char* getstack();
	int empty();
};

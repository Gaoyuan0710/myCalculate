#include "Express.h"
#include "Express.cpp"
#include "Parse.h"
#include "myFuntor.h"
#include <list>
#include <string>
#include <iostream>
#include <vector>
#include "WordParse.cpp"

using namespace std;

int main() {
	
	string info = "sin(30)";
	string result = firstdeal(info);
	cout << result << endl;

	list <Express*> Express_p;
	vector <ExpressNumber*> ExpressNumber_p;
	vector <ExpressOperator*> ExpressOperator_p;

	wordParse wordTest(result, Express_p, ExpressNumber_p, ExpressOperator_p);
	
	wordTest.Parse();
	Express_p = wordTest.returnVextor();

	for (list <Express*>::iterator tmp = Express_p.begin(); tmp != Express_p.end(); tmp++) {
		cout << " " << (*tmp)->getStrPart();
	}
	cout << endl;
	SyntaxParse Syntaxtest(Express_p);
	Syntaxtest.Parse();

	cout << "The result is " << endl;
	cout << info << endl;

	return 0;
}

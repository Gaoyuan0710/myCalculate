#ifndef _Parse_H_
#define _Parse_H_
#include <string>
#include <list>
#include "Express.h"
#include <iostream>

using namespace std;

class wordParse {
public:
	wordParse(const string &info , list<Express*> &container , const vector<ExpressNumber*> &Number, const vector<ExpressOperator*> &Operator) {
		this->info = info;
		this->container = container;
		this->Number = Number;
		this->Operator = Operator;
	}
	wordParse(){}
	int Parse();
	list<Express*> returnVextor() {
		return this->container;
	}
	int wordParseInit();
	int wordParseBegin();
	int wordParseFinish();
	list <Express*>::iterator priorElement(list<Express*>::iterator iter);
	list <Express*>::iterator nextElement(list<Express*>::iterator iter);
private:
	string info;
	list<Express*> container;
	vector<ExpressNumber*> Number;
	vector<ExpressOperator*> Operator;
};
class SyntaxParse {
public:
	SyntaxParse(list<Express*>&container) {
		this->container = container;
	}
	SyntaxParse(){}
	int Parse();
	int syntaxParsePrepare();
	int dealMinusAndSubstract();
	int updateOptPriority();
	int syntaxParseMain(list<Express*>::iterator begin,list<Express*>::iterator end);
	list <Express*>::iterator priorElement(list<Express*>::iterator iter);
	list <Express*>::iterator nextElement(list<Express*>::iterator iter);
private:
	list<Express*> container;
};

#endif

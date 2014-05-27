#ifndef _Express_H_
#define _Express_H_

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include "myFuntor.h"

using namespace std;


class operatorAndFunctor;

/*
 * The basic class 
 *
 */

class Express {
protected:
	string strPartInfo;
public:
	Express(string info = "") {
		this->strPartInfo = info;
	}
//	~Express(){}
	string getStrPart() const {
		return strPartInfo;
	}
	virtual bool isLegal()const {
		return !strPartInfo.empty();
	}
};

class ExpressOperator : public Express {
private:
	int numberOfOperands;  //The number of operands
	static int AnyNumbers; //This parameter can be used in the functions that dose not have certain parameters
	int priority;          //The priority of operator
	string nameOfOperator; //The name of the operator
	static int operatorNumbers; 
	operatorAndFunctor *funtor;
	static vector<ExpressOperator *> operatorList;

public:
	ExpressOperator(const string &operat,  const int numberOfOperator, const int priority, operatorAndFunctor *funtor) {
		this->nameOfOperator = operat;
		this->priority = priority;
		this->numberOfOperands = numberOfOperator;
		this->funtor = funtor;
	
	}
	ExpressOperator(const string &operat);
	ExpressOperator() {}
	int initOperatorList();
	bool ifExpressOperatorInit();
    bool ifOperator(const string &Operator);
	int getPriority()const {
		return priority;
	}
	string getStrPart() {
		return nameOfOperator;
	}
	operatorAndFunctor *getOperatorAndFuntor() {
		return funtor;
	}
	int setPriority(int priority) {
		this->priority = priority;
	}
	int getNumberOfOperands()const {
		return numberOfOperands;
	}
	int getoperatorNumbers() {
		return numberOfOperands;
	}
	vector<ExpressOperator *> &getOperatorList(){
	  return operatorList;
	}
};

class ExpressNumber : public Express {
private:
	double value;
	bool hasValidValue;
//	string numName;
	static std::vector<ExpressNumber *> SymbConstList;
public:
	ExpressNumber(double value) {
		this->value = value;
		this->hasValidValue = true;
	}
	ExpressNumber(){this->hasValidValue = false;}
	ExpressNumber(const string &str) ;
	ExpressNumber(const string &str, double num) {
		this->value = num;
		this->strPartInfo = str;
		this->hasValidValue  = true;
		//this-getStrPart
	}
	double getSymbConstNumber(const string &str);
	bool ifExpressSymbConstNumberInit();
	int ExpressSymbConstNumberInit();
	int ExpressNumberInit();
	bool ifSymbConstNumber(const string &str);
	double getValue()const;
	bool IsNumber(const string &str);
	vector <ExpressNumber *> &getVector() {
	  return SymbConstList;
	};

};
class ExpressBracket : public Express{
public:
	ExpressBracket(const string strPartInfo = ""):Express(strPartInfo) {
	};
	static bool isBracket(const string &strPartInfo) {
		return ("(" == strPartInfo || ")" == strPartInfo);
	}
	bool isLegal()const {
		return isBracket(strPartInfo);
	}
	bool isLeftBracket() {
		return "(" == strPartInfo;
	}
	bool isRightBracket() {
		return ")" == strPartInfo;
	}
	static int upPriority;
};

class ExpressIdentifier:public Express {
public:
	ExpressIdentifier(){}
	ExpressIdentifier(const string &info) {
		this->strPartInfo = info;
	}
	static bool isIndentifierString(const string &info);
	static bool isIndentifierchar(const char &c);
};

const string tmpFuhao = ",";

class  ExpressComma : public Express {
public:
	 ExpressComma():Express(tmpFuhao) {
	   this->strPartInfo = tmpFuhao;
	 }
	 bool isLegal() {
	 	return "," == strPartInfo;
	 }
	 bool isComma() {
	 	return "," == strPartInfo;
	 }

};


#endif

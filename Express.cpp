#include "Express.h"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

extern plus_functor plusor;
extern minus_functor minusor;
extern negate_functor negator;
extern multiplies_functor multiplor;
extern divides_functor dividor;
extern modulus_functor modulor;
extern abs_functor absor;
extern pow_functor powor;
extern exp_functor expor;
extern log_functor logor;
extern ln_functor lnor;
extern sqrt_functor sqrtor;
extern sin_functor sinor;
extern cos_functor cosor;
extern tan_functor tanor;
extern arcsin_functor arcsinor;
extern arccos_functor arccosor;
extern arctan_functor arctanor;
extern fact_functor fact;
extern double_factorial_functor dfactorialor;
extern cb_functor cbor;
extern max_functor maxor;
extern min_functor minor;
extern ceil_functor ceilor;
extern floor_functor flooror;
extern sinh_functor sinhor;
extern cosh_functor coshor;
extern tanh_functor tanhor;
extern avg_functor avg;
extern var_functor var;
extern sum_functor sum;
extern varp_functor varp;
extern stdev_functor stdev;
extern stdevp_functor stdevp;
extern mod_functor mod;
extern cubroot_functor cubroot;
extern yroot_functor yroot;


vector<ExpressNumber*> ExpressNumber::SymbConstList;
vector<ExpressOperator*>ExpressOperator::operatorList;
int ExpressOperator::AnyNumbers = 100;

bool ExpressNumber::ifExpressSymbConstNumberInit() {
	if(SymbConstList.empty() == true) {
		return false;
	}
	return true;
}
bool ExpressOperator::ifExpressOperatorInit() {
	if (operatorList.empty() == true) {
		return false;
	}
	return true;
}
int ExpressOperator::initOperatorList() {

	operatorList.push_back(new ExpressOperator("+", 2, 1, (operatorAndFunctor*)&plusor));		
	operatorList.push_back(new ExpressOperator("-", 2, 1, (operatorAndFunctor*)&minusor));
	operatorList.push_back(new ExpressOperator("-", 1, 2, (operatorAndFunctor*)&negator));
	operatorList.push_back(new ExpressOperator("*", 2, 2, (operatorAndFunctor*)&multiplor));
	operatorList.push_back(new ExpressOperator("/", 2, 2, (operatorAndFunctor*)&dividor));
	operatorList.push_back(new ExpressOperator("%", 2, 2, (operatorAndFunctor*)&modulor));
	operatorList.push_back(new ExpressOperator("abs", 1, 100, (operatorAndFunctor*)&absor));
	operatorList.push_back(new ExpressOperator("pow", 2, 100, (operatorAndFunctor*)&powor));
	operatorList.push_back(new ExpressOperator("^", 2, 3, (operatorAndFunctor*)&powor));
	operatorList.push_back(new ExpressOperator("exp", 1, 100, (operatorAndFunctor*)&expor));
	operatorList.push_back(new ExpressOperator("log", 2, 100, (operatorAndFunctor*)&logor));
	operatorList.push_back(new ExpressOperator("ln", 1, 100, (operatorAndFunctor*)&lnor));
	operatorList.push_back(new ExpressOperator("sqrt", 1, 100, (operatorAndFunctor*)&sqrtor));
	operatorList.push_back(new ExpressOperator("sin", 1, 100, (operatorAndFunctor*)&sinor));
	operatorList.push_back(new ExpressOperator("cos", 1, 100, (operatorAndFunctor*)&cosor));
	operatorList.push_back(new ExpressOperator("tan", 1, 100, (operatorAndFunctor*)&tanor));
	operatorList.push_back(new ExpressOperator("arcsin", 1, 100, (operatorAndFunctor*)&arcsinor));
	operatorList.push_back(new ExpressOperator("arccos", 1, 100, (operatorAndFunctor*)&arccosor));
	operatorList.push_back(new ExpressOperator("arctan", 1, 100, (operatorAndFunctor*)&arctanor));
	operatorList.push_back(new ExpressOperator("fact", 1, 100, (operatorAndFunctor*)&fact));
	operatorList.push_back(new ExpressOperator("!", 1, 3, (operatorAndFunctor*)&fact));
	operatorList.push_back(new ExpressOperator("!!", 1, 100, (operatorAndFunctor*)&dfactorialor));
	operatorList.push_back(new ExpressOperator("cb", 2, 100, (operatorAndFunctor*)&cbor));
	operatorList.push_back(new ExpressOperator("max", AnyNumbers, 100, (operatorAndFunctor*)&maxor));
	operatorList.push_back(new ExpressOperator("min", AnyNumbers, 100, (operatorAndFunctor*)&minor));
	operatorList.push_back(new ExpressOperator("ceil", 1, 100, (operatorAndFunctor*)&ceilor));
	operatorList.push_back(new ExpressOperator("floor", 1, 100, (operatorAndFunctor*)&flooror));
	operatorList.push_back(new ExpressOperator("sinh", 1, 100, (operatorAndFunctor*)&sinhor));
	operatorList.push_back(new ExpressOperator("cosh", 1, 100, (operatorAndFunctor*)&coshor));
	operatorList.push_back(new ExpressOperator("tanh", 1, 100, (operatorAndFunctor*)&tanhor));

	operatorList.push_back(new ExpressOperator("avg", AnyNumbers, 100, (operatorAndFunctor*)&avg));
	operatorList.push_back(new ExpressOperator("sum", AnyNumbers, 100, (operatorAndFunctor*)&sum));
	operatorList.push_back(new ExpressOperator("var", AnyNumbers, 100, (operatorAndFunctor*)&var));
	operatorList.push_back(new ExpressOperator("varp", AnyNumbers, 100, (operatorAndFunctor*)&varp));
	operatorList.push_back(new ExpressOperator("stdev", AnyNumbers, 100, (operatorAndFunctor*)&stdev));	
	operatorList.push_back(new ExpressOperator("stdevp", AnyNumbers, 100, (operatorAndFunctor*)&stdevp));
	operatorList.push_back(new ExpressOperator("mod", 2, 100, (operatorAndFunctor*)&mod));
	operatorList.push_back(new ExpressOperator("cubroot", 1, 100, (operatorAndFunctor*)&cubroot));
	operatorList.push_back(new ExpressOperator("yroot", 2, 100, (operatorAndFunctor*)&yroot));
	return 0;
}
int ExpressNumber::ExpressSymbConstNumberInit() {
	SymbConstList.push_back(new ExpressNumber("pi",3.1415926535));
	SymbConstList.push_back(new ExpressNumber("e",2.718281828));

	return 0;
}

int ExpressBracket::upPriority = 9999;

bool ExpressOperator::ifOperator(const string &str) 
{

	if(!ifExpressOperatorInit()) {
		initOperatorList();
	}
	for (vector<ExpressOperator*>:: iterator i = operatorList.begin(); i != operatorList.end(); i++) {
		if(str == (*i)->getStrPart()) { 
			return true;
		}
	}

	return false;
}
bool ExpressNumber::ifSymbConstNumber(const string & str) {

	if (!ifExpressSymbConstNumberInit()) {
		ExpressSymbConstNumberInit();
	}
	if (SymbConstList.empty()) {
		return false;
	}

	for (vector<ExpressNumber*>::iterator iter = SymbConstList.begin(); iter != SymbConstList.end(); iter++) {
		if ((*iter)->getStrPart() == str) {
			return true;
		}
	}
	return false;
}
double ExpressNumber::getValue()const {
	if (hasValidValue == true)
		return this->value;
	else
	{
		string errMsg = string("The number \"") + this->getStrPart() + "\" has no value.";
		return 0;
	}
}

bool ExpressNumber::IsNumber(const string &str) {
	if(0 == str.size()) {
		return false;
	}

	int numDot = 0;
//	cout << "check " << str << endl;

	for(string::size_type i = 0; i != str.size(); i++) {
			if('-' == str[i]) {
				if(0 != i) {
					return false;
				}
			}
			else if (0 != isdigit(str[i])) {
				continue;
			}
			else if ('.' == str[i]) {
				if( ( 0 == i ) || (str.size() - 1 == i ) ) {
					return false;
				}
				if( 0 == isdigit(str[i - 1])) {
					return false;
				}
				if(1 < ++numDot) {
					return false;
				}
			}
			else {
				return false;
			}
	}
	return true;
}


double ExpressNumber::getSymbConstNumber(const string &str) {
	for (vector<ExpressNumber*>::const_iterator it = SymbConstList.begin(); it != SymbConstList.end(); it++) {
		if ((*it)->getStrPart() == str) {
			return (*it)->getValue();
		}
	}
	return 0;
}
ExpressNumber::ExpressNumber(const string &str) {
  double value = 0.0;
  this->hasValidValue = false;
  
  if(str.empty())
	{
		value = 0.0;
	}

	bool withOppSgn = false;	//默认是正数

	string str_temp = str;
	if('-' == str_temp[0])
	{
		str_temp = str_temp.substr(1, str_temp.size()-1); //第一位为负号时，字符串从第二位开始截取
		withOppSgn = true; //符号为负
	}

	if(IsNumber(str_temp) == true )  
	{
		value = atof(str_temp.c_str()); // 转换为相应的浮点数
	}

	if(withOppSgn)
	{
		value = -value;
	}

	this->strPartInfo = str;
	this->value = value;
	this->hasValidValue = true;
}

ExpressOperator::ExpressOperator(const string &opt) : Express(opt) {
	numberOfOperands		= 0;
	priority	= 0;
	funtor		= NULL;
	nameOfOperator = "";
	if(!ifExpressOperatorInit()) initOperatorList();


	for(vector<ExpressOperator*>::const_iterator iter = operatorList.begin(); iter != operatorList.end(); iter++)
	{
		if(opt == (*iter)->getStrPart())
		{
			numberOfOperands		= (*iter)->numberOfOperands;
			priority	= (*iter)->priority;
			funtor		= (*iter)->funtor;
			nameOfOperator = (*iter)->getStrPart();
			break;
		}
	}

}

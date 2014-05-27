#include "Express.h"
#include "Parse.h"
#include "myString.h"
#include "myString.cpp"
#include <typeinfo>
#include "myFuntor.h"
#include "myFuntor.cpp"
#include "check.cpp"
#include "calculate.cpp"

extern plus_functor plusor;
extern minus_functor minusor;
extern negate_functor negator;
extern multiplies_functor multiplor;
extern divides_functor dividor;

/*
 * get  the prior element *
 */
list <Express*>::iterator SyntaxParse::priorElement(list<Express*>::iterator iter) {
	list<Express*>::iterator tmp = iter;

	return --tmp;
}
/*
 * get  the next element *
 */

list <Express*>::iterator SyntaxParse::nextElement(list<Express*>::iterator iter) {
	list<Express*>::iterator tmp = iter;

	return ++tmp;
}
/*
 * get  the prior element *
 */

list <Express*>::iterator wordParse::priorElement(list<Express*>::iterator iter) {
	list<Express*>::iterator tmp = iter;

	return --tmp;
}

/*
 * get  the next element *
 */

list <Express*>::iterator wordParse::nextElement(list<Express*>::iterator iter) {
	list<Express*>::iterator tmp = iter;

	return ++tmp;
}
/*
 * The process of Word Parse
 */
int wordParse::Parse () {
	int status;

	status = wordParseInit();
	if (0 != status) {
		return -1;
	}
	status = wordParseBegin();
	if (0 != status) {
		return -2;
	}


	status = wordParseFinish();
	if (0 != status) {
		return -3;
	}

}
/*
 * Init the lists of SymbConstNumber and operator
 */
int wordParse::wordParseInit() {
	int status;
	class ExpressNumber tmpNum;
	class ExpressOperator tmpOperator;

	status = tmpNum.ExpressSymbConstNumberInit();


	Number = tmpNum.getVector();


	if (0 != status) {
		return -1;
	}

	status = tmpOperator.initOperatorList();

	Operator = tmpOperator.getOperatorList();

	if (0 != status) {
		return -2;
	}

	return 0;
}
/*
 * get different parts of the express
 */
int wordParse::wordParseBegin() {
	string::size_type externalPosition = 0;

	while (externalPosition < info.size()) {
		if (0 != isdigit(info[externalPosition])) {           // get the number in express
			string::size_type internalPosition;

			for (internalPosition = externalPosition + 1; internalPosition <= info.size(); internalPosition++) {
				if (info.size() != internalPosition) {
					if (info.size() == 1 + internalPosition) {
						if ( (!isNumberAll(info.substr(externalPosition, internalPosition - externalPosition + 1)))
							&& (isNumberAll(info.substr(externalPosition, internalPosition - externalPosition)))) {
							break;
						}
					}
					if ((!isNumberAll(info.substr(externalPosition, internalPosition - externalPosition + 1))) && (!isNumberAll(info.substr(externalPosition, internalPosition - externalPosition)))) {
						internalPosition--;
						break;
					}
				}
			}
			container.push_back(new ExpressNumber(info.substr(externalPosition, internalPosition - externalPosition)));
			externalPosition = internalPosition;
		}
		else if ( 0 != isalpha(info[externalPosition])) {     //get the operator in express 
				string::size_type internalPosition;

			for (internalPosition = externalPosition + 1; internalPosition <= info.size(); internalPosition++) {
				class ExpressIdentifier tmpIdenti;
				if (!tmpIdenti.isIndentifierString(info.substr(externalPosition, internalPosition - externalPosition))) {
					internalPosition--;
					break;
				}
			}
			container.push_back(new ExpressIdentifier(info.substr(externalPosition, internalPosition - externalPosition)));
			externalPosition = internalPosition;
		}
		else {
			if (('(' == info[externalPosition]) || (')') == info[externalPosition]) {  // deal "(" or ")"
				container.push_back(new ExpressBracket(info.substr(externalPosition, 1)));
				externalPosition++;
			}
			else if (',' == info[externalPosition]) {                                  // deal  ","
				container.push_back(new ExpressComma());
				externalPosition++;
			}
			else {                                                                     // deal operator
				bool isOpeartor = false;

				for (string::size_type internalPosition = info.size(); internalPosition > externalPosition; internalPosition--) {
					class ExpressOperator tmpOperator;
					if ((tmpOperator.ifOperator(info.substr(externalPosition, internalPosition - externalPosition)) == true )) {
						container.push_back(new  ExpressOperator(info.substr(externalPosition, internalPosition- externalPosition)));
						externalPosition = internalPosition;
						isOpeartor = true;
						break;
					}
				}
				if (!isOpeartor) {
					return -3;
				}
			}
		}
	}
	return 0;
}

int wordParse::wordParseFinish() {
	if (container.empty()) {
		return -1;
	}

	for (list<Express *>::iterator iter = container.begin(); iter != container.end(); iter++) {
		class ExpressNumber tmpNum;
		class ExpressOperator tmpOper;

	
		if (tmpOper.ifOperator((*iter)->getStrPart()) == true) {
			ExpressOperator *opt = new ExpressOperator((*iter)->getStrPart());
			delete *iter;
			*iter = opt;
		}
		else if (tmpNum.ifSymbConstNumber((*iter)->getStrPart()) == true) {
			double tmp = tmpNum.getSymbConstNumber((*iter)->getStrPart());

			cout << "is SymbCon " << (*iter)->getStrPart() << endl;
			ExpressNumber *num = new ExpressNumber((*iter)->getStrPart(), tmp);
			delete *iter;
			*iter = num;
		}
	}
	return 0;
}

int SyntaxParse::Parse() {
	int status = 0;

	status = syntaxParsePrepare();

	if (0 != status) {
		return -1;
	}


	status = syntaxParseMain(container.begin(), container.end());
	if (0 != status) {
		return -2;
	}

	double yuan = calculate(container, container.begin(), container.end());
	cout << "The result is "  << yuan << "~~~" << endl;
}
int SyntaxParse::syntaxParsePrepare() {
	int status = 0;

	status = dealMinusAndSubstract();



	if (0 != status) {
		return -1;
	}


	status = updateOptPriority();

	if (0 != status) {
		return -2;
	}

	return 0;
}

/* 
 * deal "-" as operator or negative
 */
int SyntaxParse::dealMinusAndSubstract() {
	if (container.empty()) {
		return 0;
	}

	for (list<Express*>::iterator iter = container.begin(); iter != container.end(); iter++) {
		if ( (typeid(*(*iter)) == typeid(ExpressOperator)) && ((*iter)->getStrPart() == "-")) {
			ExpressOperator *opt = dynamic_cast<ExpressOperator*>(*iter);

			if ((container.begin() == iter) || ((*(priorElement(iter)))->getStrPart() == "(")
				|| ((*(priorElement(iter)))->getStrPart() == ",")) {
				if (opt->getPriority() != 2) {
					delete *iter;
					opt = NULL;
					*iter = NULL;
					*iter = new ExpressOperator("-",1,2,(operatorAndFunctor*) & negator);
				}
			} 
			else if ((container.begin() != iter) && (((*(priorElement(iter)))->getStrPart() == ")") 
				|| (typeid(*(*(priorElement(iter)))) == typeid(ExpressNumber)))) {
				if (opt->getPriority() != 1) {
					delete *iter;
					opt = NULL;
					*iter = NULL;
					*iter = new ExpressOperator("-",2,1,(operatorAndFunctor*)&minusor);
				}
			}
		}
	}
	return 0;
}

/*
 * modify the priority in different "()"
 */
int SyntaxParse::updateOptPriority() {
	if (container.empty()) {
		return 0;
	}
	int level = 0;

	for (list <Express*>::iterator iter = container.begin(); iter != container.end(); iter++) {
		if (typeid(*(*iter)) == typeid(ExpressOperator)) {

				ExpressOperator *opt = dynamic_cast<ExpressOperator*>(*iter);

			opt->setPriority(opt->getPriority() + level * ExpressBracket::upPriority);
			
		}
		else if (typeid(*(*iter)) == typeid(ExpressBracket)) {
			ExpressBracket *bracket = dynamic_cast<ExpressBracket*>(*iter);
			if (bracket->isLeftBracket()) {
				level++;
			}
			else if (bracket->isRightBracket()) {
				level--;
			}
			else {
				cout << "The unrecognised charactor " << endl;
				return -1;
			}
		}
	}
	return 0;
}


int SyntaxParse::syntaxParseMain(const list<Express*>::iterator Begin, const list<Express*>::iterator End) {
	list<Express*>::iterator expressBegin = Begin;
	list<Express*>::iterator expressEnd = End;

	if (expressEnd == nextElement(expressBegin)) {
		if (typeid(*(*expressBegin)) == typeid(ExpressNumber)) {
			return 0;
		}
		else {
			cout << "The wrong charactor in the express " << endl;
			return -1;
		}
	}
	if ((((*(expressBegin))->getStrPart() == "(") && ((*(priorElement(expressEnd)))->getStrPart() == ")") 
		&& checkBracket(container, nextElement(expressBegin), priorElement(expressEnd)))) {
		expressBegin++;
		expressEnd--;
	}
	else {
		container.insert(expressBegin, new ExpressBracket("("));
		container.insert(expressEnd, new ExpressBracket(")"));
		expressEnd--;
	}

	int lowestPriority = 9999999;
	ExpressOperator *primeOpt = NULL, *tmpOpt = NULL;
	list<Express*>::iterator i = expressEnd;

	for (list<Express*>::iterator iter = expressBegin; iter != expressEnd; iter++ ) {
		if (typeid(*(*iter)) == typeid(ExpressOperator)) {
			tmpOpt = dynamic_cast<ExpressOperator*>(*iter);
			if(tmpOpt->getPriority() <= lowestPriority) {
				primeOpt = tmpOpt;
				i = iter;
				lowestPriority = tmpOpt->getPriority();
			}
		}
	}
	
	if ((NULL == primeOpt) || (expressEnd == i)) {
		cout << "the Priority wrong " << endl;
		return -2;
	}


	if (ExpressIdentifier::isIndentifierString(primeOpt->getStrPart()) == 0) {
		if (1 == primeOpt->getNumberOfOperands()) {
			if (expressBegin != i) {
				if (((*i)->getStrPart() == "!" || (*i)->getStrPart() == "!!") && 
				expressEnd == nextElement(i)) {
					container.insert(expressBegin, *i);
					*i = NULL;
					container.erase(i);
					return syntaxParseMain(expressBegin, expressEnd);
				}
				else {
					cout << " The wrong operator " << endl;
					return -3;
				}
			}
			list <Express*>::iterator firstNumBegin = nextElement(i);
			return syntaxParseMain(firstNumBegin, expressEnd);
		}
		else if (2 == primeOpt->getNumberOfOperands()) {
			if ((expressBegin == i) || (priorElement(expressEnd) == i)) {
				cout << "the operator is wrong " << endl;
				return -4;
			}
			list<Express*>::iterator thisNumberEnd = nextElement(i);
			list<Express*>::iterator nextNumberbegin = nextElement(i);

			container.insert(expressBegin, *i);
			*i = NULL;
			container.erase(i);

			int status = syntaxParseMain(expressBegin, thisNumberEnd);
			if (0 != status) {
				return status;
			}

			status = syntaxParseMain(nextNumberbegin, expressEnd);
			if (0 != status) {
				return status;
			}
			return 0;
		}
	}
	else if ((ExpressIdentifier::isIndentifierString(primeOpt->getStrPart()) != 0)) {
		if (i != expressBegin) {
			cout << "The operator wrong "  << primeOpt->getStrPart()  << " ??"<< endl;
			return -10;
		}
		expressBegin++;
		if (!(((*(expressBegin))->getStrPart() == "(") && ((*(priorElement(expressEnd)))->getStrPart() == ")") && checkBracket(container, nextElement(expressBegin), priorElement(expressEnd)))) {
			cout << "The function wrong " << endl;
			return -11;
		}
		list<Express*>::iterator thisParamsLeftBracket = expressBegin;
		list<Express*>::iterator thisparamsRightBracket = expressEnd;

		list<Express*>::iterator thisParamsBegin = nextElement(expressBegin);
		list<Express*>::iterator thisParamsEnd = priorElement(expressEnd);

		int numberOfOperands = primeOpt->getNumberOfOperands();
		int numberParams = 0;
		int level = 0;

		list <Express*>:: iterator paramBegin, paramEnd;
		paramBegin = thisParamsBegin;
		paramEnd = thisParamsEnd;

		bool isEndOfParam = false;

		for (list<Express*>::iterator tmp = paramBegin; tmp != nextElement(thisParamsEnd); tmp++) {
			if (tmp == thisParamsEnd) {
				isEndOfParam = true;
				paramEnd = thisParamsEnd;
			}
			else if ("(" == (*tmp)->getStrPart()) {
				level++;
			}
			else if (")" == (*tmp)->getStrPart()) {
				level--;
			}

			if (0 != level) {
				continue;
			}

			if (typeid(*(*tmp)) == typeid(ExpressComma)) {
				isEndOfParam = true;
				paramEnd = tmp;
			}

			if (isEndOfParam) {
				numberParams++;
				if (numberParams > numberOfOperands) {
					cout << "the function wrong " << endl;
					return -10;
				}
				if (0 != syntaxParseMain(paramBegin, paramEnd)) {
					return -1;
				}
				paramBegin = nextElement(tmp);
				isEndOfParam = false;
			}
		}
		level = 0;
		thisParamsBegin = nextElement(thisParamsLeftBracket);
		thisParamsEnd = priorElement(thisparamsRightBracket);

		list<Express*>::iterator comma;
		for (list<Express*>::iterator tmp = thisParamsBegin; tmp != thisParamsEnd; tmp++ ) {
			if (typeid(*(*tmp)) == typeid(ExpressBracket)) {
				if ("(" == (*tmp)->getStrPart()) {
					level++;
				}
				else if (")" == (*tmp)->getStrPart()) {
					level--;
				}
				continue;
			}
			if (typeid(*(*tmp)) == typeid(ExpressComma)) {
				if(0 == level) {
					comma = tmp;
					tmp++;
					delete *comma;
					*comma  = NULL;
					container.erase(comma);
					tmp--;
				}
			}
		}
		list<Express*>::iterator thisparamsRightBracketPart = priorElement(thisparamsRightBracket);
		delete *thisParamsLeftBracket;
		delete *thisparamsRightBracketPart;
		*thisParamsLeftBracket = NULL;
		*thisparamsRightBracketPart = NULL;
		container.erase(thisParamsLeftBracket);
		container.erase(thisparamsRightBracketPart);
	}
	else {
		cout << "Undefined operator " << endl;
	}
	return 0;
}

#include <list>
#include <iostream>
#include "Express.h"
#include "myString.h"

using namespace std;

/*
 *
 * check whether the numbers of Bracket is right *
 *
 * 
 */
bool checkBracket(list<Express*> &container,list<Express*>::iterator Begin, list<Express*>::iterator End) {
	int level = 0;

	for(list<Express*>::iterator iter = Begin; iter != End; iter++) {
		if((*iter)->getStrPart()=="(") {
			level++;
		}
		else if((*iter)->getStrPart()==")") {
			if(0 > --level) {
				return false;
			}
		}
	}
	return 0==level;                     
}
/*
 * The first part of deal *
 * Aim: (1) deal space ;
 *      (2) deal express such as (2) to 2;
 *      (3) replace all "[" or "]" with "(" or ")";
 *      (4) deal the numbers such as ".7" to "0.7";
 *      (5) deal the numbers such as "-7" to "0-7";
 *      (6) deal the numbers such as "+7" to "7";
 */
string firstdeal(string &str) {
	string resultFirst;
	string resultSecond;
	string resultThird;
	int level = 0;
	ExpressOperator tmpOpt;

	for(string::size_type i = 0; i < str.size(); i++) {
		if (str[i] == '(' || str[i] == '[') {
			str[i] = '(';
			level++;
		}
		else if (str[i] == ')' || str[i] == ']') {
			str[i] = ')';
			level--;
		}
		if(str[i] == ' ') {
			continue;
		}
		str[i] = tolower(str[i]);
		resultFirst += str[i];
	}
	if (level != 0) {
		cout << "The Bracket is not enougth " << endl;
		exit(0);
	}


	int flag = 0;
	string tmpNUm;
	ExpressNumber tmpNumber;

	for(string::size_type i = 0; i < resultFirst.size(); i++) {
	if ((resultFirst[i] == '.' ) && (i == 0)) {
			resultSecond += '0';
			resultSecond += resultFirst[i];
			continue;
		}
		if ((resultFirst[i] == '-' ) && ((i == 0) || (resultFirst[i - 1] == '('))) {
			resultSecond += '0';
			resultSecond += resultFirst[i];
			continue;
		}
		if (resultFirst[i] == '+' && (resultFirst[i - 1] == '(')){
			continue;
		}
		if ((resultFirst[i] == '.') && (isdigit(resultFirst[i - 1]) != true)) {
			resultSecond += '0';
		}
		if ((resultFirst[i] == '.') && (isdigit(resultFirst[i + 1]) != true)) {
			resultSecond += resultFirst[i];
			resultSecond += '0';
			continue;
		}
		resultSecond += resultFirst[i];

			
	}
	if (level != 0) {
		cout << "The Bracket is less " << endl;
		exit(0);
	}

	
	for (string::size_type i = 0; i != resultSecond.size(); i++) {
		if (resultSecond[i] == '(') {
			string::size_type j = resultSecond.size();
			int flag = 0;
			
			for (;j > i;  j--) {

				if((isNumberAll(resultSecond.substr(i + 1 , j - i - 1)) == true) && (resultSecond[j] == ')') && (!isgraph(resultSecond[j]))) {
					flag = 1;

					resultThird += resultSecond.substr(i + 1, j - i -1);


					i = j ;
					break;
				}
			}
			if (flag != 1) {
				resultThird += resultSecond[i];
			}
		}
		else {
			resultThird += resultSecond[i];
		}

}

	return resultThird; 
}

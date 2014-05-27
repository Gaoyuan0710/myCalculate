#include "Parse.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <ctype.h>
using namespace std;

bool isNumberAll(const string &str) {
	if (0 == str.size()) {
		return false;
	}

	int numRadixPoint = 0;

	for (string::size_type i = 0; i != str.size(); i++) {
		if ('-' == str[i]) {
			if (0 != i) {
				return false;
			}
		}
		else if (0 != isdigit(str[i])) {
				continue;
			}
			else if ('.' == str[i]) {
				if ( (0 == i) || ((str.size() - 1) == i)) {
					return false;
				}
				if (0 == isdigit(str[i - 1])) {
					return false;
				}
				if (1 < ++numRadixPoint) {
					return false;
				}
			}
			else {
				return false;
			}
		}
	return true;
}

bool ExpressIdentifier::isIndentifierchar(const char &c) {
	if (0 != isalpha(c)) {
		return true;
	}
	else if (0 != isdigit(c)) {
		return true; 
	}

	return false;
}
bool ExpressIdentifier::isIndentifierString(const string &str) {
	if (0 == str.size()) {
		return false;
	}

	if (0 == isalpha(str[0])) {
		return false;
	} 
	for (string::size_type i = 0; i != str.size(); i++) {
		ExpressIdentifier  tmpIndenty;

		if (false == tmpIndenty.isIndentifierchar(str[i])) {
			return false;
		}
	}
	return true;
}

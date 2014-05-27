#include "Express.h"
#include "Parse.h"
#include <list>
#include <iostream>
#include "myFuntor.h"
using namespace std;



double calculate(list<Express*> &container, const list<Express*>::iterator expressBegin, const list<Express*>::iterator expressEnd)
{
SyntaxParse tmpYuan;



	if(expressEnd == tmpYuan.nextElement(expressBegin))
	{
		ExpressNumber *ptr_num = dynamic_cast<ExpressNumber*>(*expressBegin);
		return ptr_num->getValue();
	}

	list<Express*>::iterator it_opt = tmpYuan.nextElement(expressBegin);

	int level = 0;
	list<Express*>::iterator subexpressBegin, subexpressEnd;
	subexpressBegin = expressBegin;
	subexpressEnd = expressEnd;
	bool isEndSubExp = false;
	for(list<Express*>::iterator it_loop=tmpYuan.nextElement(it_opt); it_loop!=tmpYuan.priorElement(expressEnd); it_loop++)
	{
		if((*it_loop)->getStrPart()=="(")
		{
			if(0==level)
			{
				subexpressBegin = it_loop;
			}
			level++;
		}
		else if((*it_loop)->getStrPart()==")")
		{
			level--;
			if(0==level)
			{
				subexpressEnd = tmpYuan.nextElement(it_loop);
				it_loop = tmpYuan.priorElement(subexpressBegin);
				isEndSubExp = true;
			}
		}

		if(isEndSubExp)
		{
			double valueOfSubExp = calculate(container, subexpressBegin, subexpressEnd);
			list<Express*>::iterator it_del;
			for(list<Express*>::iterator it_temp=subexpressBegin; it_temp!=subexpressEnd; it_temp++)
			{
				it_del = it_temp;
				it_temp--;
				delete *it_del;
				*it_del = NULL;
			container.erase(it_del);
			
			}
			// 从最中间的括号开始（或者优先级最高的表达式开始） 计算后用结果代替原表达式


			container.insert(subexpressEnd, new ExpressNumber(valueOfSubExp));
			isEndSubExp = false;



		}
	}

	vector<double> parameter;
	ExpressNumber *ptr_num = NULL;
	for(list<Express*>::iterator it_loop=tmpYuan.nextElement(it_opt); it_loop != tmpYuan.priorElement(expressEnd); it_loop++)
	{
		ptr_num = dynamic_cast<ExpressNumber*>(*it_loop);
		parameter.push_back(ptr_num->getValue());
	}

	ExpressOperator *ptr_opt = dynamic_cast<ExpressOperator*>(*it_opt);
	operatorAndFunctor *funtor = ptr_opt->getOperatorAndFuntor();

	return (*funtor)(parameter);
} 

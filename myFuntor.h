#ifndef _myFuntor_H_
#define _myFuntor_H_
#include <cmath>
#include <functional>
using namespace std;

#define PI 3.1415926

class operatorAndFunctor
{
public:
	operatorAndFunctor(){}
	virtual ~operatorAndFunctor(){}
	virtual double operator()(vector<double> &parameters)const = 0;
};

class plus_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		plus<double> plus_std_functor;
		return plus_std_functor(parameters[0], parameters[1]);
	}
};

class minus_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		minus<double> minus_std_functor;
		return minus_std_functor(parameters[0], parameters[1]);
	}
};

class negate_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		negate<double> negate_std_functor;
		return negate_std_functor(parameters[0]);
	}
};

class multiplies_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		multiplies<double> multiplies_std_functor;
		return multiplies_std_functor(parameters[0], parameters[1]);
	}
};

class divides_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		divides<double> divides_std_functor;
		if (abs(parameters[1]) < 10e-9)
		{
			string errMsg = "A error of \"divisor is zero\" has occur.";
			return 0;
		}
		return divides_std_functor(parameters[0], parameters[1]);
	}
};

class modulus_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		modulus<int> modulus_std_functor;
		if ((int)parameters[1] <= 0)
		{
			string errMsg = "The second parameter of modulus must be positive.";
			return 0;
		}
		return modulus_std_functor((int)parameters[0], (int)parameters[1]);
	}
};

class abs_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return abs(parameters[0]);
	}
};

class pow_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
	//	std::cout << " " << parameters[0] << " " << parameters[1] << endl;
		return pow(parameters[0], parameters[1]);
	}
};

class exp_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return exp(parameters[0]);
	}
};

class log_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		if (parameters[0] <= 0 || parameters[1] <= 0)
		{
			string errMsg = "The parameters of log() both must be positive.";
			return 0;
		}
		return log(parameters[0]) / log(parameters[1]);
	}
};

class ln_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		if (parameters[0] <= 0)
		{
			string errMsg = "The parameter of ln() must be positive.";
			return 0;
		}
		return log(parameters[0]);
	}
};

class sqrt_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		if (parameters[0] < 0)
		{
			string errMsg = "The parameter of sqrt() must be non-negative.";
			return 0;
		}
		
		return sqrt(parameters[0]);
	}
};

class sin_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return sin(parameters[0] * PI / 180);
	}
};

class cos_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return cos(parameters[0] * PI / 180);
	}
};

class tan_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return tan(parameters[0] * PI / 180);
	}
};

class arcsin_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return asin(parameters[0]);
	}
};

class arccos_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return acos(parameters[0]);
	}
};

class arctan_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return atan(parameters[0]);
	}
};

class fact_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		int n = (int)parameters[0];

		if (n < 0)
			return -1;

		if (n == 0)
			return 1;

		int i, result = 1;
		for (i = 1; i <= n; i++) 
			result *= i;

		return result;
	}
};

class double_factorial_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		int n = (int)parameters[0];

		if (n < 0)
			return -1;

		if (n == 0)
			return 0;

		int i, result = 1;
		for (i = (n % 2 == 0 ? 2 : 1); i <= n; i += 2) 
			result *= i;

		return result;
	}
};

class cb_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		int m = (int)parameters[0];
		int n = (int)parameters[1];

		if (n <= 0 || m <= 0 || m > n)
			return 0;

		int numerator = 1;
		int denominator  = 1;
		for (int i = 0; i < m; i++)
		{
			numerator *= (n-i);
			denominator *= (m-i);
		}

		return (double)numerator / (double)denominator;
	}
};

class max_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		double curtMax = parameters[0];
		for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++)
		{
			if (*it > curtMax)
				curtMax = *it;
		}

		return curtMax;
	}
};

class min_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		double curtMax = parameters[0];
		for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++)
		{
			if (*it < curtMax)
				curtMax = *it;
		}

		return curtMax;
	}
};

class ceil_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return ceil(parameters[0]);
	}
};

class floor_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return floor(parameters[0]);
	}
};

class sinh_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return sinh(parameters[0]);
	}
};

class cosh_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return cosh(parameters[0]);
	}
};

class tanh_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return tanh(parameters[0]);
	}
};

class avg_functor : public operatorAndFunctor 
{
	public:
		double operator()(vector<double> &parameters)const {
			double sum = 0;
			int num = 0;

			for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
				sum += *it;
				num++;
			}
//cout << sum << endl;
			return (sum / num);
		}
};
class sum_functor : public operatorAndFunctor {
	public:
		double operator()(vector<double> &parameters)const {
			double sum = 0.0;

			for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
				sum += *it;
			}
			return sum;
		}
};
class var_functor :public operatorAndFunctor {
	public:
		double operator()(vector<double> &parameters)const {
			double sum = 0.0;
			double Svar = 0.0;
			int num = 0;
			double average = 0.0;

			for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
				sum += *it;
				num++;
			}

			average = sum / num;

			for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
				Svar += pow(average - *it, 2);
			}
			return (Svar / (num - 1));
		}
};
class varp_functor : public operatorAndFunctor {
	public:
		double operator()(vector<double> &parameters)const {
			double sum = 0.0;
			double Svarp = 0.0;
			int num = 0;
			double average = 0.0;
			
			for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
				sum += *it;
				num++;
			}

			average = sum / num;

			for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
				Svarp += pow(average - *it, 2);
			}
			return (Svarp / num);
		}
};

class stdev_functor : public operatorAndFunctor {
	public:
		double operator()(vector<double> &parameters)const {
			double sum = 0.0;
			double Svar = 0.0;
			int num = 0;
			double average = 0.0;
			
			for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
				sum += *it;
				num++;
			}

			average = sum / num;

			for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
				Svar += pow(average - *it, 2);
			}
		 	return (pow((Svar / (num - 1)), 0.5));
		}
};

class stdevp_functor : public operatorAndFunctor {
	public:
		double operator()(vector<double> &parameters)const {
			double sum = 0.0;
			double Svarp = 0.0;
			int num = 0;
			double average = 0.0;
			
			for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
				sum += *it;
				num++;
			}

			average = sum / num;

			for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
				Svarp += pow(average - *it, 2);
			}
		 	return (pow((Svarp / num), 0.5));
		}
};
class mod_functor : public operatorAndFunctor {
	public:
		double operator()(vector<double> &parameters)const {
			return ((int)parameters[0] % (int)parameters[1]);
		}
};


class cubroot_functor : public operatorAndFunctor {

	double operator()(vector<double> &parameters)const
	{
		return pow(parameters[0], 0.5);
	}
};

class yroot_functor : public operatorAndFunctor {
	double operator()(vector<double> &parameters)const {
		return pow(parameters[0], 1.0 / parameters[1]);
	}
};
#endif


/*
class ceil_functor : public operatorAndFunctor
{
public:
	double operator()(vector<double> &parameters)const
	{
		return ceil(parameters[0]);
	}
};

*/

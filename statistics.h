#include <cmath>
#include <functional>
#include <vector>

using namespace std;

class avg_funtor:public operatorAndFuntor {
	public:
		double operator()(vector<double> &parameters)const {
			double sum = 0;
			int num = 0;

			for (vector<double>::const_iterator it = parameters.begin(); it != parameters.end(); it++) {
				sum += *it;
			}
			return (sum / num);
		}
};


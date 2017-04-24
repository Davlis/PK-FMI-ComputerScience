#include <iostream>
#include <functional>
#include <vector>
#include <cmath>

#define MAX_ITERATIONS 100
#define EPSILON_RESIDUUM 1e-16
#define EPSILON_ESTIMATOR 1e-16

using namespace std;

vector<double> newton(double x0, double y0, double z0);

int main(void) {
	vector<double> solution = newton(1.1, 3.0, 3.0);
	
	printf("\n  x = % .10f\n  y = % .10f\n  z = % .10f\n", solution[0], solution[1], solution[2]);
	
	return 0;
}

vector<double> newton(double x0, double y0, double z0) {
	const function<double(double, double, double)> equation[3] = {
		[](double x, double y, double z) { return x * x + y * y + z * z - 2; },
		[](double x, double y, double z) { return x * x + y * y - 1; 		 },
		[](double x, double y, double z) { return x * x - y; 				 }
	};
	
	/**
		http://www.wolframalpha.com/input/?i=inverse+matrix+of+jacobian+matrix+of+%7Bx%5E2%2By%5E2%2Bz%5E2-2,x%5E2%2By%5E2-1,x%5E2-y%7D
	**/	
	const function<double(double, double, double)> partial_derivative[3][3] = {
		{ [](double x, double y, double z) { return 0;           }, [](double x, double y, double z) { return  1 / (4 * y * x + 2 * x); }, [](double x, double y, double z) { return y / (2 * y * x + x); } },
		{ [](double x, double y, double z) { return 0;           }, [](double x, double y, double z) { return  1 / (2 * y + 1);         }, [](double x, double y, double z) { return 1 / (-2 * y - 1);    } },
		{ [](double x, double y, double z) { return 1 / (2 * z); }, [](double x, double y, double z) { return -1 / (2 * z);             }, [](double x, double y, double z) { return 0;                   } }
	};
	
	int iter;
	double x_next[3];
	double solution[3] = { x0, y0, z0 };
	
	const function<double(void)> calculate_residuum = [&equation, &solution]() { 
		double temp = 0;
		for(int i = 0; i < 3; i++)
			temp += fabs(equation[i](solution[0], solution[1], solution[2]));
		return temp / 3;
	};

	const function<double(double[])> calculate_estimator = [](double* x_next) {
		double temp = 0;
		for(int i = 0; i < 3; i++)
			temp += fabs(x_next[i]);
		return temp / 3;
	};
	
	double residuum = calculate_residuum();
	double estimator = calculate_estimator(solution);
	
	printf("\n  _____________________________|NEWTON METHOD FOR SYSTEM OF EQUATIONS|______________________________ \n");
	printf(  " |    # |         x |         y |         z |                  residuum |                 estimator |\n");
	printf(  " |======|===========|===========|===========|===========================|===========================|\n");
	
	for(iter = 1; iter < MAX_ITERATIONS && residuum > EPSILON_RESIDUUM && estimator > EPSILON_ESTIMATOR; iter++) {	
		printf(" | %4d | % 9.5f | % 9.5f | % 9.5f | % 25.20f | % 25.20f |\n", iter, solution[0], solution[1], solution[2], residuum, estimator);
		for(int i = 0; i < 3; i++) {
			x_next[i] = 0;
			for(int j = 0; j < 3; j++)
				x_next[i] += partial_derivative[i][j](solution[0], solution[1], solution[2]) * equation[j](solution[0], solution[1], solution[2]);
		}
		
		for(int i = 0; i < 3; i++)
			solution[i] -= x_next[i];
			
		residuum = calculate_residuum();
		estimator = calculate_estimator(x_next);
	}
	
	printf(" | %4d | % 9.5f | % 9.5f | % 9.5f | % 25.20f | % 25.20f |\n", iter, solution[0], solution[1], solution[2], residuum, estimator);
	printf(" |______|___________|___________|___________|___________________________|___________________________|\n");
	
	printf(" |___ Reason of stopping: %s ____________________________________________|\n\n", 
		iter >= MAX_ITERATIONS ? "exceeded number of iterations" : residuum <= EPSILON_RESIDUUM ? "fulfilled residuum condition " : 
		estimator <= EPSILON_ESTIMATOR ? "fulfilled estimator condition" : "method divergent             ");
	
	return vector<double>(solution, solution + sizeof(solution) / sizeof(solution[0]));
}
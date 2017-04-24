#include <iostream>
#include <functional>
#include <cmath>

#define MAX_ITERATIONS 100
#define EPSILON_RESIDUUM 1e-10
#define EPSILON_ESTIMATOR 1e-10

using namespace std;

double picard(function<double(double)> fx, double x0);
double bisection(function<double(double)> fx, double from, double to);
double newton(function<double(double)> fx, double x0);
double newton(function<double(double)> fx, function<double(double)> derivative, double x0);
double secant(function<double(double)> fx, double x0, double x1);

int main(void) {
	function<double(double)> fx = [](double x) { return sin(x / 4) * sin(x / 4) - x; };
	function<double(double)> gx = [](double x) { return tan(2 * x) - x - 1; };

	printf("\n");
	printf("  _______________ FIRST FUNCTION ________________ \n");
	printf(" |                                               |\n");
	printf(" |            f(x) = sin^2(x / 4) - x            |\n");
	printf(" |_______________________________________________|\n");
	printf("  f(x) = 0 => x = %.20f\n", picard(fx, 1.5));
	printf("  f(x) = 0 => x = %.20f\n", bisection(fx, -1.0, 1.567));
	printf("  f(x) = 0 => x = %.20f\n", newton(fx, 1.5));
	printf("  f(x) = 0 => x = %.20f\n", secant(fx, 1.5, 1.0));
	printf("\n");
	
	printf("\n");
	printf("  ______________ SECOND FUNCTION ________________ \n");
	printf(" |                                               |\n");
	printf(" |            g(x) = tan(2x) - x - 1             |\n");
	printf(" |_______________________________________________|\n");
	printf("  f(x) = 0 => x = %.20f\n", picard(gx, 1.5));
	printf("  f(x) = 0 => x = %.20f\n", bisection(gx, 0.4, 0.5));
	printf("  f(x) = 0 => x = %.20f\n", newton(gx, 0.3));
	printf("  f(x) = 0 => x = %.20f\n", secant(gx, 1.5, 1.0));
	printf("\n");
	
	return 0;
}

double derivative(function<double(double)> fx, double x0) {
	return (fx(x0 + 1e-10) - fx(x0)) / 1e-10;
}

double picard(function<double(double)> fx, double x0) {
	const function<double(double)> picard_fx = [&fx](double x) { return fx(x) + x; };
	int iter;
	double x = x0;
	double y = fx(x0);
	double residuum = fabs(fx(x));
	double estimator = fabs(x - y);

	printf("\n  ______________________________________|PICARD METHOD|_____________________________________ \n");
	printf(  " |    # |                         x |                  residuum |                 estimator |\n");
	printf(  " |======|===========================|===========================|===========================|\n");
	
	if(derivative(picard_fx, x0) <= 1) {
		for (iter = 1; iter < MAX_ITERATIONS && residuum > EPSILON_RESIDUUM && estimator > EPSILON_ESTIMATOR; iter++) {
			printf(" | %4d | % 25.20f | % 25.20f | % 25.20f |\n", iter, x, residuum, estimator);
			x = y;
			y = picard_fx(x);
			residuum = fabs(fx(x));
			estimator = fabs(x - y);
		}
		
		printf(" | %4d | % 25.20f | % 25.20f | % 25.20f |\n", iter, x, residuum, estimator);
		printf(" |______|___________________________|___________________________|___________________________|\n");
	}
	
	printf(" |___ Reason of stopping: %s ____________________________________|\n\n", 
		iter >= MAX_ITERATIONS ? "exceeded number of iterations" : residuum <= EPSILON_RESIDUUM ? "fulfilled residuum condition " : 
		estimator <= EPSILON_ESTIMATOR ? "fulfilled estimator condition" : "method divergent             ");
	
	return x;
}

double bisection(function<double(double)> fx, double from, double to) {
	int iter;
	double middle = (from + to) / 2;
	double residuum = fabs(fx(middle));
	double estimator = fabs(from - to) / 2;
	
	printf("\n  _____________________________________|BISECTION METHOD|___________________________________ \n");
	printf(  " |    # |                         x |                  residuum |                 estimator |\n");
	printf(  " |======|===========================|===========================|===========================|\n");
	
	if(fx(from) * fx(to) <= 0) {
		for (iter = 1; iter < MAX_ITERATIONS && residuum > EPSILON_RESIDUUM && estimator > EPSILON_ESTIMATOR; iter++) {
			printf(" | %4d | % 25.20f | % 25.20f | % 25.20f |\n", iter, middle, residuum, estimator);
		
			if (fx(from) * fx(middle) < 0)
				to = middle;
			else
				from = middle;
			
			middle = (from + to) / 2.0;
			residuum = fabs(fx(middle));
			estimator = fabs(from - to) / 2.0;
		}
		printf(" | %4d | % 25.20f | % 25.20f | % 25.20f |\n", iter, middle, residuum, estimator);
		printf(" |______|___________________________|___________________________|___________________________|\n");
	}
	
	printf(" |___ Reason of stopping: %s ____________________________________|\n\n", 
		iter >= MAX_ITERATIONS ? "exceeded number of iterations" : residuum <= EPSILON_RESIDUUM ? "fulfilled residuum condition " : 
		estimator <= EPSILON_ESTIMATOR ? "fulfilled estimator condition" : "interval must contains root  ");

	return middle;
}

double newton(function<double(double)> fx, double x0) {
	return newton(fx, [&fx](double x) { return derivative(fx, x); }, x0);
}

double newton(function<double(double)> fx, function<double(double)> derivative, double x0) {
	int iter;
	double x = x0;
	double x_next = x - (fx(x) / derivative(x));
	double residuum = fabs(fx(x));
	double estimator = fabs(x - x_next);

	printf("\n  _______________________________________|NEWTON METHOD|____________________________________ \n");
	printf(  " |    # |                         x |                  residuum |                 estimator |\n");
	printf(  " |======|===========================|===========================|===========================|\n");
	for(iter = 1; iter < MAX_ITERATIONS && residuum > EPSILON_RESIDUUM && estimator > EPSILON_ESTIMATOR; iter++) {
		printf(" | %4d | % 25.20f | % 25.20f | % 25.20f |\n", iter, x, residuum, estimator);
		
		x = x_next;
		x_next = x - (fx(x) / derivative(x));
		residuum = fabs(fx(x_next));
		estimator = fabs(x_next - x);
	}
	printf(" | %4d | % 25.20f | % 25.20f | % 25.20f |\n", iter, x, residuum, estimator);
	printf(" |______|___________________________|___________________________|___________________________|\n");
	
	printf(" |___ Reason of stopping: %s ____________________________________|\n\n", 
		iter >= MAX_ITERATIONS ? "exceeded number of iterations" : residuum > EPSILON_RESIDUUM ? "fulfilled residuum condition " : "fulfilled estimator condition");
	
	return x;
}

double secant(function<double(double)> fx, double x0, double x1) {
	int iter;
	double x_next = x1 - fx(x1) * ((x1 - x0) / (fx(x1) - fx(x0)));
	double residuum = fabs(fx(x0));
	double estimator = fabs(x_next - x0);
	
	printf("\n  _______________________________________|SECANT METHOD|____________________________________ \n");
	printf(  " |    # |                         x |                  residuum |                 estimator |\n");
	printf(  " |======|===========================|===========================|===========================|\n");
	for(iter = 1; iter < MAX_ITERATIONS && residuum > EPSILON_RESIDUUM && estimator > EPSILON_ESTIMATOR; iter++) {
		printf(" | %4d | % 25.20f | % 25.20f | % 25.20f |\n", iter, x1, residuum, estimator);
	
		x0 = x1;
		x1 = x_next;
		x_next = x1 - fx(x1) * ((x1 - x0) / (fx(x1) - fx(x0)));
		residuum = fabs(fx(x1));
		estimator = fabs(x_next - x1);
	}
	printf(" | %4d | % 25.20f | % 25.20f | % 25.20f |\n", iter, x1, residuum, estimator);
	printf(" |______|___________________________|___________________________|___________________________|\n");
	
	printf(" |___ Reason of stopping: %s ____________________________________|\n\n", 
		iter >= MAX_ITERATIONS ? "exceeded number of iterations" : residuum > EPSILON_RESIDUUM ? "fulfilled residuum condition " : "fulfilled estimator condition");
	
	return x1;
}
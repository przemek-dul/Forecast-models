#include "Winters.h"

int main() 

{
	std::vector<double> data = { 1, 1.24, 1.3, 1.5, 1.8, 2.1, 2.3, 2.2, 2.5, 2.2 };
	double alpha = 0.5;
	double beta = 0.5;
	double gamma = 0.5;
	int m = 3;
	
	Winters model = Winters(data, alpha, beta, gamma, m, "additive");
	model.show_error();
	model.optimization(0.05);
	model.show_error();
	model.model_info();
	model.show_forecast();
	model.plot();
	return 0;
}
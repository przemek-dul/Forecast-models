#include <iostream>
#include "Brown.h"
#include "Holt.h"
#include "Winters.h"
#include <string>

int main()
{

	std::vector<double> Data = { 1, 1.25, 1.8, 1.6, 1.5, 2.2, 2.4 };
	double alpha = 0.5;

	Brown B = Brown(Data, alpha);
	B.optimization(0.05);
	B.model_info();

	return 0;

}


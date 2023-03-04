#include "Brown.h"

Brown::Brown(std::vector<double> input, double alpha1) : Model(input)
{
	alpha = alpha1;
	if (inputProp)
	{
		output = Brown::calculate();
		Model::caluclate_error();
	}
	
}

std::vector<double>Brown::calculate() 
{
	double toAdd{};
	std::vector<double> arr = {};
	for (int i = 0; i < input.size() + 1; i++)
	{
		if (arr.size() == 0)
		{
			toAdd = std::accumulate(input.begin(), input.end(), 0.0) / input.size();
		}
		else
		{
			toAdd = alpha * input[i - 1] + (1 - alpha) * arr[i - 1];
		}
		arr.push_back(toAdd);
	}

	return arr;
}

void Brown::optimization(double step = 0.01)
{
	if (inputProp)
	{
		double newAlpha = 0;
		double currV = 100;
		alpha = 0;
		while (alpha <= 1) {
			output = Brown::calculate();
			Model::caluclate_error();
			if (var < currV)
			{
				newAlpha = alpha;
				currV = var;
			}
			alpha = alpha + step;
		}
		alpha = newAlpha;
		output = Brown::calculate();
		Model::caluclate_error();
	}
	else
	{
		std::cout << "Error: Check input" << std::endl;
	}
}

void Brown::model_info() 
{
	std::cout << "alpha=" << alpha << std::endl;
}
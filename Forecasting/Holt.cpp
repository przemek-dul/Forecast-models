#include "Holt.h"

Holt::Holt(std::vector<double> input, double alpha1, double beta1) : Model(input)
{
	alpha = alpha1;
	beta = beta1;
	if (inputProp)
	{
		output = Holt::calculate();
		Model::caluclate_error();
	}
	
}

std::vector<double>Holt::calculate()
{
	double toAdd{};
	double yt1{}, yt2{};
	double bt1{}, bt2{};

	std::vector<double> arr = {};

	yt1 = std::accumulate(input.begin(), input.end(), 0.0) / input.size();
	bt1 = input[1] - input[0];

	for (int i = 0; i < input.size() + 1; i++)
	{
		toAdd = yt1 + bt1;
		arr.push_back(toAdd);

		if (i < input.size())
		{
			yt2 = alpha * input[i] + (1 - alpha) * (yt1 + bt1);
			bt2 = beta * (yt2 - yt1) + (1 - beta) * bt1;

			yt1 = yt2;
			bt1 = bt2;
		}	
	}

	return arr;
}

void Holt::optimization(double step = 0.01)
{
	if (inputProp)
	{
		double newAlpha = 0;
		double newBeta = 0;
		double currV = 100;

		alpha = 0;
		while (alpha <= 1)
		{
			beta = 0;
			while (beta <= 1)
			{
				output = Holt::calculate();
				Model::caluclate_error();
				if (var < currV)
				{
					newAlpha = alpha;
					newBeta = beta;
					currV = var;
				}
				beta = beta + step;
			}

			alpha = alpha + step;
		}
		alpha = newAlpha;
		beta = newBeta;
		output = Holt::calculate();
		Model::caluclate_error();
	}

	else
	{
		std::cout << "Error: Check input" << std::endl;
	}
}

void Holt::model_info()
{
	std::cout << "alpha=" << alpha << std::endl;
	std::cout << "beta=" << beta << std::endl;
}

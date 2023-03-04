#include "Winters.h"

Winters::Winters(std::vector<double>
	input, double alpha1, double beta1, double gamma1, int m1, std::string type1) : Model(input)
{
	type = type1;
	m = m1;
	alpha = alpha1;
	beta = beta1;
	gamma = gamma1;
	Model::check_input();
	if(inputProp)
	{
		output = Winters::calculate();
		Model::caluclate_error();
	}
}

std::vector<double> Winters::calculate()
{
	double at{}, ct{}, dt{}, toAdd{};
	double at0 = std::accumulate(input.begin(), input.begin() + m, 0.0)/m;
	double ct0 = (std::accumulate(input.begin() + m, input.begin() + 2 * m, 0.0) - std::accumulate(input.begin(), input.begin() + m, 0.0)) / m;
	std::vector<double> dts{};
	std::vector<double> arr = {};
	int k = 0;

	for (int i = 0; i < input.size(); i++) 
	{
		if (i < m)  
		{
			dt = m * input[i] / std::accumulate(input.begin(), input.begin() + m, 0.0);
			dts.push_back(dt);
		}
		else 
		{
			if (type == "additive") 
			{
				at = alpha * (input[i] - dts[k]) + (1 - alpha) * (at0 + ct0);
				ct = beta * (at - at0) + (1 - beta) * ct0;
				dt = gamma * (input[i] - at) + (1 - gamma) * dts[k];

				dts.push_back(dt);
				toAdd = at0 + ct0 + dts[k];
				arr.push_back(toAdd);
			}
			if (type == "multiplicative")
			{
				at = (alpha*input[i]/dts[k])+(1-alpha)*(at0+ct0);
				ct = beta*(at-at0)+(1-beta)*ct0;
				dt = (gamma*input[i]/at)+(1-gamma)*dts[k];

				dts.push_back(dt);
				toAdd = (at0 + ct0) * dts[k];
				arr.push_back(toAdd);
			}
			
			k++;
			at0 = at;
			ct0 = ct;
		}

	}
	for (int i = 0; i < m; i++) 
	{
		if (type == "additive") 
		{
			toAdd = at + ct * (input.size() + 1 + i - input.size()) + dts[k];
		}

		if (type == "multiplicative")
		{
			toAdd = (at + ct * (input.size() + 1 + i - input.size())) * dts[k];
		}
		
		arr.push_back(toAdd);
		k++;
	}
	return arr;
}


void Winters::optimization(double step = 0.01)
{
	if (inputProp) 
	{
		double newAlpha = 0;
		double newBeta = 0;
		double newGamma = 0;
		double currV = 100;

		alpha = 0;
		while (alpha <= 1)
		{
			beta = 0;
			while (beta <= 1)
			{
				gamma = 0;
				while (gamma <= 1)
				{
					output = Winters::calculate();
					Model::caluclate_error();
					if (var < currV)
					{
						newAlpha = alpha;
						newBeta = beta;
						newGamma = gamma;
						currV = var;
					}
					gamma = gamma + step;
				}

				beta = beta + step;
			}

			alpha = alpha + step;
		}
		alpha = newAlpha;
		beta = newBeta;
		gamma = newGamma;
		output = Winters::calculate();
		Model::caluclate_error();
	}
	else 
	{
		std::cout << "Error: Check input" << std::endl;
	}
}

void Winters::model_info()
{
	std::cout << "alpha=" << alpha << std::endl;
	std::cout << "beta=" << beta << std::endl;
	std::cout << "gamma=" << beta << std::endl;
	std::cout << "m=" << m << std::endl;
}


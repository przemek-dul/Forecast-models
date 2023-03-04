#include "Model.h"

Model::Model(std::vector<double> input) : input(input) 
{
	
}

std::vector<double> Model::calculate() 
{
	return std::vector<double>();
};

void Model::optimization(double step) {};

void Model::results()
{
	std::cout << "[ ";
	for (auto value : output)
	{
		std::cout << value << " ";
	}
	std::cout << "]\n";
}

void Model::plot()
{
	std::ofstream plot("plot.gnu");
	plot << "set terminal wxt persist\n";
	plot << "set xlabel 'time [-]'\n";
	plot << "set ylabel 'quantity [-]'\n";
	plot << "set grid\n";
	plot << "plot '-' with linespoints title 'Model', '-' with linespoints title 'Input'\n";

	for (size_t i = 0; i < output.size(); i++)
	{
		plot << i+m << " " << output[i] << std::endl;
	}
	plot << "e\n";

	for (size_t i = 0; i < input.size(); i++)
	{
		plot << i << " " << input[i] << std::endl;
	}

	plot << "e\n";

	plot.close();

	system("gnuplot plot.gnu");
}

void Model::caluclate_error()
{
	double sum = 0;
	double n = 0;
	for (int i = 0; i < input.size()-m; i++)
	{
		sum = sum + std::pow(input[i+m] - output[i], 2);
	}

	if (input.size()-m < 30)
	{
		n = input.size()-m;
	}

	else
	{
		n = input.size()-m + 1;
	}

	std = std::sqrt(sum / n);
	var = std * 100 / (std::accumulate(input.begin(), input.end(), 0.0) / input.size());
}

void Model::show_error()
{
	std::cout << "std=" << std << std::endl;
	std::cout << "V=" << var << "[%]" << std::endl;
}
void Model::show_forecast() 
{
	if (inputProp) 
	{
		std::cout << "[ ";
		if (m == 0) 
		{
			std::cout << output[output.size() - 1]<<" ]"<<std::endl;
		}
		else 
		{
			for (int i = 1; i <= m; i++) 
			{
				std::cout << output[output.size() - i] << " ";
			}
			std::cout << "]"<<std::endl;
		}
	}
};
void Model::check_input() 
{
	auto min_it = std::min_element(input.begin(), input.end());
	if (input.size() < 3)
	{
		std::cout << "Error: Input must have atlest 3 elements" << std::endl;
		inputProp = false;
	}
	if (alpha < 0 || alpha > 1 || beta < 0 || beta > 1 || gamma < 0 || gamma >1)
	{
		std::cout << "Error: The parameters must be in the range(0, 1)" << std::endl;
		inputProp = false;
	}
	if (m < 1)
	{
		std::cout << "Error: Dynamic lookahead must be greather than 0" << std::endl;
		inputProp = false;
	}

	if (m > input.size() / 2)
	{
		std::cout << "Error: Dynamic lookahead must be lower or equal half of input size" << std::endl;
		inputProp = false;
	}
	if (*min_it < 0)
	{
		std::cout << "Error: Input's elements must be positive" << std::endl;
		inputProp = false;
	}

	if (type != "additive" && type != "multiplicative") 
	{
		std::cout << "Error: Wrong model type, you can chose 'additive' or 'multiplicative'" << std::endl;
		inputProp = false;
	}
	
};


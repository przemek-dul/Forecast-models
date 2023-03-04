#pragma once
#include <vector>
#include <iostream>
#include <numeric>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <string>
class Model
{
protected:
	std::vector<double> input{};
	std::vector<double> output{};
	double std{};
	double var{};
	double alpha = 0;
	double beta = 0;
	double gamma = 0;
	int m=0;
	bool inputProp = true;
	std::string type = "multiplicative";

	virtual std::vector<double>calculate();

	void caluclate_error();
	void check_input();

public:
	Model(std::vector<double> input);
	void results();
	void plot();
	void show_error();
	void show_forecast();

	virtual void optimization(double step);

};


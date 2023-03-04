#pragma once
#include "Model.h"
class Winters : public Model
{
protected:
	virtual std::vector<double>calculate() override;

public:
	Winters(std::vector<double> input, double alpha, double beta, double gamma, int m, std::string type);
	virtual void optimization(double step) override;
	void model_info();
};


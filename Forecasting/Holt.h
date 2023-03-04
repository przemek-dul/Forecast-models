#pragma once
#include "Model.h"
class Holt : public Model
{
protected:
	virtual std::vector<double>calculate() override;

public:
	Holt(std::vector<double> input, double alpha, double beta);
	virtual void optimization(double step) override;
	void model_info();

};



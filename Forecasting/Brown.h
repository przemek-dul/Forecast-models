#pragma once
#include "Model.h"
class Brown : public Model 
{
protected:
	virtual std::vector<double>calculate() override;

public:
	Brown(std::vector<double> input, double alpha);
	virtual void optimization(double step) override;
	void model_info();

	
};


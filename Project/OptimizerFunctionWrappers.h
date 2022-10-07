#ifndef OPTIMIZER_FUNCTION_WRAPPERS_H
#define OPTIMIZER_FUNCTION_WRAPPERS_H

#include "OptimizerFunction.hpp"
#include "VAGrisFunction.h"
#include "GKLSFunction.h"
#include "problem_interface.h"

class FunctionWrapperCommon : public optimizercore::OptimizerFunction
{
public:
	virtual ~FunctionWrapperCommon() = 0;
	virtual void SetFunctionNumber(int) = 0;
	virtual void GetMinPoint(double *x) const = 0;
	virtual double GetMinValue() const = 0;
};

class VAGRisFunctionWrapper : public FunctionWrapperCommon
{
private:
	vagrisfunction::VAGrisFunction mFunction;
	double GetMinXCoordinate() const;
	double GetMinYCoordinate() const;
public:
	VAGRisFunctionWrapper();
	virtual ~VAGRisFunctionWrapper();

	void SetFunctionNumber(int num) override;
	void GetMinPoint(double *x) const override;
	double Calculate(const double *x) override;
	double GetMinValue() const override;
};

class GKLSFunctionWrapper : public FunctionWrapperCommon
{
private:
	unsigned mDimension;
	double* mTmpArgument;
	gklsfunction::GKLSFunction mFunction;
public:
	GKLSFunctionWrapper();
	GKLSFunctionWrapper(gklsfunction::GKLSClass type, unsigned);
	virtual ~GKLSFunctionWrapper();

	void SetClassType(gklsfunction::GKLSClass type, unsigned);
	void SetFunctionNumber(int num) override;
	void SetDimension(unsigned value);
	double Calculate(const double *x) override;
	double GetMinValue() const override;
	void GetMinPoint(double *x) const override;
};

class CustomProblemWrapper : public FunctionWrapperCommon
{
private:
	IProblem* mFunction;
public:
	CustomProblemWrapper();
	CustomProblemWrapper(IProblem*);
	virtual ~CustomProblemWrapper();

	void SetFunctionNumber(int num) override;
	void SetDimension(unsigned value);
	double Calculate(const double* x) override;
	double GetMinValue() const override;
	void GetMinPoint(double* x) const override;
};
#endif
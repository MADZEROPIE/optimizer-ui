#include "OptimizerFunctionWrappers.h"

FunctionWrapperCommon::~FunctionWrapperCommon() {
}

VAGRisFunctionWrapper::VAGRisFunctionWrapper() {
}

VAGRisFunctionWrapper::~VAGRisFunctionWrapper() {
}

void VAGRisFunctionWrapper::SetFunctionNumber(int num) {
    mFunction.SetFunctionNumber(num);
}

double VAGRisFunctionWrapper::GetMinXCoordinate() const {
    return mFunction.GetMinimumXCoordinate(mFunction.GetFunctionNumber());
}

double VAGRisFunctionWrapper::GetMinYCoordinate() const {
    return mFunction.GetMinimumYCoordinate(mFunction.GetFunctionNumber());
}

double VAGRisFunctionWrapper::Calculate(const double *x) {
    return mFunction.EvaluateFunction(x[0], x[1]);
}

double VAGRisFunctionWrapper::GetMinValue() const {
    return mFunction.EvaluateFunction(GetMinXCoordinate(), GetMinYCoordinate());
}

void VAGRisFunctionWrapper::GetMinPoint(double *x) const {
    x[0] = GetMinXCoordinate();
    x[1] = GetMinYCoordinate();
}

GKLSFunctionWrapper::GKLSFunctionWrapper() : mTmpArgument(nullptr), mDimension(2) {
}

GKLSFunctionWrapper::GKLSFunctionWrapper(gklsfunction::GKLSClass type, unsigned dim)
    : mTmpArgument(nullptr) {
    SetClassType(type, dim);
}

void GKLSFunctionWrapper::SetClassType(gklsfunction::GKLSClass type, unsigned dimension) {
    mFunction.SetFunctionClass(type, dimension);
    mDimension = mFunction.GetDimension();

    if (mTmpArgument != nullptr)
        delete[] mTmpArgument;
    mTmpArgument = new double[mDimension];
}

void GKLSFunctionWrapper::SetFunctionNumber(int num) {
    mFunction.SetFunctionNumber(num);
}

double GKLSFunctionWrapper::Calculate(const double *x) {
    return mFunction.EvaluateDFunction(x);
}

GKLSFunctionWrapper::~GKLSFunctionWrapper() {
    if (mTmpArgument != nullptr)
        delete[] mTmpArgument;
}

double GKLSFunctionWrapper::GetMinValue() const {
    return mFunction.GetGlobalMinimumValue();
}

void GKLSFunctionWrapper::GetMinPoint(double *x) const {
    mFunction.GetGlobalMinimumPoint(mFunction.GetFunctionNumber(), x);
}

void GKLSFunctionWrapper::SetDimension(unsigned value) {
    mDimension = value;
    mFunction.SetDimension(mDimension);
}

CustomProblemWrapper::CustomProblemWrapper() : mFunction(nullptr) {
}

CustomProblemWrapper::CustomProblemWrapper(IProblem *problem) : mFunction(problem) {
}

CustomProblemWrapper::~CustomProblemWrapper() {
}

void CustomProblemWrapper::SetFunctionNumber(int num) {
}

void CustomProblemWrapper::SetDimension(unsigned value) {
}

double CustomProblemWrapper::Calculate(const double *x) {
    return mFunction->CalculateFunctionals(x, 0);
}

double CustomProblemWrapper::GetMinValue() const {
    double val = NAN;
    mFunction->GetOptimumValue(val);
    return val;
}

void CustomProblemWrapper::GetMinPoint(double *x) const {
    mFunction->GetOptimumPoint(x);
}
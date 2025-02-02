#ifndef OPTIMIZER_SOLUTION_HPP
#define OPTIMIZER_SOLUTION_HPP

#include "OptimizerCoreGlobal.hpp"

namespace optimizercore {
class EXPORT_API OptimizerSolution final {
private:
    int mIteratinsCount;
    unsigned mDimension;
    double mOptimumValue;
    double mOneDimOptimumPoint;
    SharedVector mOptimumPoint;

    bool mIsInitialized;

public:
    OptimizerSolution();
    OptimizerSolution(int iterationsCount, double optimumValue, double oneDimOptimumPoint,
                      unsigned dimension, SharedVector optimumPoint);
    OptimizerSolution(const OptimizerSolution& sol) = default;
    ~OptimizerSolution() {
    }

    int GetIterationsCount() const;
    double GetOneDimOptimumPoint() const;
    double GetOptimumValue() const;
    SharedVector GetOptimumPoint() const;

private:
    void CheckIsInitialized() const;
};
}  // namespace optimizercore
#endif
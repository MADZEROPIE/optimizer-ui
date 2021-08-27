#include "OptimazerAlgorithmNested.hpp"

using namespace optimizercore;
using namespace optimizercore::utils;

void optimizercore::OptimizerAlgorithmNested::AllocMem() {}

void optimizercore::OptimizerAlgorithmNested::InitializeInformationStorage() {
  if (!mIsAlgorithmMemoryAllocated) {
    AllocMem();
    mIsAlgorithmMemoryAllocated = true;
  }

  mZ = HUGE_VAL;
  mGlobalM = 1;
  mMaxIntervalNorm = 0;

  mSearchInformationStorage.clear();




}

void optimizercore::OptimizerAlgorithmNested::UpdateGlobalM(
    std::set<OptimizerNestedTrialPoint>::iterator &) {}

int optimizercore::OptimizerAlgorithmNested::UpdateRanks(bool isLocal)
{
    return 0;
}

bool optimizercore::OptimizerAlgorithmNested::InsertNewTrials(int trialsNumber)
{
    return false;
}

OptimizerSolution optimizercore::OptimizerAlgorithmNested::DoLocalVerification(OptimizerSolution startPoint)
{
    return OptimizerSolution();
}

optimizercore::OptimizerAlgorithmNested::OptimizerAlgorithmNested()
{
}

optimizercore::OptimizerAlgorithmNested::~OptimizerAlgorithmNested()
{
}

void optimizercore::OptimizerAlgorithmNested::SetTask(OptimizerFunctionPtr function, OptimizerSpaceTransformation spaceTransform)
{
}

void optimizercore::OptimizerAlgorithmNested::SetThreadsNum(int num)
{
}

void optimizercore::OptimizerAlgorithmNested::SetParameters(OptimizerParameters params)
{
}

OptimizerResult optimizercore::OptimizerAlgorithmNested::StartOptimization(const double* xOpt, StopCriterionType stopType)
{
    return OptimizerResult();
}

double optimizercore::OptimizerAlgorithmNested::GetLipschitzConst() const
{
    return 0.0;
}

OptimazerNestedSearchSequence optimizercore::OptimizerAlgorithmNested::GetSearchSequence() const
{
    return OptimazerNestedSearchSequence();
}

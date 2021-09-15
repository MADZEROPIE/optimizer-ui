#include "OptimazerAlgorithmNested.hpp"
#include <cassert>

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
    mIsAlgorithmMemoryAllocated = false;

    mLocalStartIterationNumber = 1;
    mNumberOfThreads = 1;
    mMaxNumberOfIterations = 5000;
    mNextPoints = nullptr;
    mNextTrialsPoints = nullptr;
    r = 2;
    mLocalTuningMode = LocalTuningMode::None;

    mIsTaskInitialized = false;
    mIsParamsInitialized = false;
}

optimizercore::OptimizerAlgorithmNested::~OptimizerAlgorithmNested()
{
}

void optimizercore::OptimizerAlgorithmNested::SetTask(OptimizerFunctionPtr function, OptimizerSpaceTransformation spaceTransform)
{
    assert(function);

    mTargetFunctionSmartPtr = function;
    mTargetFunction = function.get();
    mSpaceTransform = spaceTransform;

    mIsTaskInitialized = true;
}

void optimizercore::OptimizerAlgorithmNested::SetThreadsNum(int num)
{
    if (num > 0 && num < 100)
    {
        if (mNextPoints != nullptr)
            delete[] mNextPoints;
        mNumberOfThreads = num;
        if (mNextTrialsPoints)
            delete[] mNextTrialsPoints;
        mNextTrialsPoints = new OptimizerNestedTrialPoint[num];
        for (int i = 0; i < mMethodDimention; ++i) {
            mNextTrialsPoints->x.resize(mMethodDimention);
        }
    }
}

void optimizercore::OptimizerAlgorithmNested::SetParameters(OptimizerParameters params)
{
    assert(params.algDimention);
    assert(params.eps > 0);
    assert(params.localAlgStartIterationNumber > 0);
    assert(params.mapTightness > 5 && params.mapTightness <= 20);
    assert(params.maxIterationsNumber > 0);
    assert(params.localMixParameter >= 0 && params.localMixParameter <= 20);
    assert(params.r != nullptr);
    assert(params.numberOfThreads > 0);
    assert(params.reserves != nullptr);
    //assert(params.adaptiveLocalTuningParameter >= 0 &&
    //	params.adaptiveLocalTuningParameter <= 1);

    mLocalStartIterationNumber = params.localAlgStartIterationNumber;
    eps = params.eps;
    if (params.localMixParameter <= 10) {
        mLocalMixParameter = params.localMixParameter;
        mLocalMixType = true;
    }
    else {
        mLocalMixParameter = 20 - params.localMixParameter;
        mLocalMixType = false;
    }
    mNeedLocalVerification = params.localVerification;
    mAlpha = params.localExponent;
    mMethodDimention = params.algDimention;
    mMapTightness = params.mapTightness;
    mMapType = static_cast<int>(params.mapType);
    mMaxNumberOfIterations = params.maxIterationsNumber;
    mLocalTuningMode = params.localTuningMode;
    r = *params.r;
    if (mNextPoints)
        utils::DeleteMatrix(mNextPoints, mNumberOfThreads);
    mNextPoints = utils::AllocateMatrix<double>(mNumberOfThreads, mMethodDimention);
    this->SetThreadsNum(params.numberOfThreads);

    mIsParamsInitialized = true;
}

OptimizerResult optimizercore::OptimizerAlgorithmNested::StartOptimization(const double* xOpt, StopCriterionType stopType)
{

    return OptimizerResult();
}

double optimizercore::OptimizerAlgorithmNested::GetLipschitzConst() const
{
    return mGlobalM;
}

OptimazerNestedSearchSequence optimizercore::OptimizerAlgorithmNested::GetSearchSequence() const
{
    return OptimazerNestedSearchSequence(mSearchInformationStorage, mMethodDimention);
}

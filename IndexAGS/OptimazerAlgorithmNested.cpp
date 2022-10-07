#include "OptimazerAlgorithmNested.hpp"
#include "HookeJeevesLocalMethod.hpp"

#include <cassert>
#include <algorithm>

using namespace optimizercore;
using namespace optimizercore::utils;

optimizercore::OptimizerAlgorithmNested::OptimizerAlgorithmNested() {
    mIsAlgorithmMemoryAllocated = false;

    mLocalStartIterationNumber = 1;
    mNumberOfThreads = 1;
    mMaxNumberOfIterations = 5000;
    mNextPoints = nullptr;
    mNextTrialsPoints = nullptr;
    r = 2;
    mLocalTuningMode = LocalTuningMode::None;
    mIntervalsForTrials = nullptr;
    mIsTaskInitialized = false;
    mIsParamsInitialized = false;
}

optimizercore::OptimizerAlgorithmNested::~OptimizerAlgorithmNested() {
    delete[] mNextTrialsPoints;
    delete[] mIntervalsForTrials;
    if (mNextPoints)
        utils::DeleteMatrix(mNextPoints, mNumberOfThreads);
}

void optimizercore::OptimizerAlgorithmNested::AllocMem() {
}

void optimizercore::OptimizerAlgorithmNested::InitializeInformationStorage() {
    if (!mIsAlgorithmMemoryAllocated) {
        AllocMem();
        mIsAlgorithmMemoryAllocated = true;
    }

    mZ = HUGE_VAL;
    mBaseM = 1;
    mMaxIntervalNorm = 0;

    mSearchInformationStorage.clear();
}

void optimizercore::OptimizerAlgorithmNested::UpdateGlobalM(  // GlobalM is LipschitzConst on first
                                                              // recursion layer
    std::set<OptimizerNestedTrialPoint>::iterator& newPointIt,
    const std::set<OptimizerNestedTrialPoint>& localStorage) {
    double max = mBaseM;
    if (max == 1)
        max = 0;

    auto leftPointIt = newPointIt;
    auto rightPointIt = newPointIt;
    --leftPointIt;
    ++rightPointIt;

    double leftIntervalNorm = newPointIt->x[0] - leftPointIt->x[0];
    double rightIntervalNorm = rightPointIt->x[0] - newPointIt->x[0];

    max = fmax(fmax(fabs(newPointIt->val - leftPointIt->val) / leftIntervalNorm,
                    fabs(rightPointIt->val - newPointIt->val) / rightIntervalNorm),
               max);

    mMaxIntervalNorm = 0;
    auto currentPointIt = localStorage.begin();
    auto nextPointIt = currentPointIt;
    ++nextPointIt;

    while (nextPointIt != localStorage.cend()) {
        //	if (currentPointIt->x != newPointIt->x)
        //		max = fmax(fabs(newPointIt->val - currentPointIt->val) /
        //			pow(fabs(newPointIt->x - currentPointIt->x), 1.0 / mMethodDimension),
        //max);

        if (mLocalTuningMode != LocalTuningMode::None)
            // if (mLocalTuningMode == LocalTuningMode::Maximum)
            mMaxIntervalNorm = fmax(nextPointIt->x[0] - currentPointIt->x[0], mMaxIntervalNorm);

        ++currentPointIt;
        ++nextPointIt;
    }
    // if (currentPointIt->x != newPointIt->x)
    //	max = fmax(fabs(newPointIt->val - currentPointIt->val) /
    //	pow(fabs(newPointIt->x - currentPointIt->x), 1.0 / mMethodDimension), max);

    // printf("%e |", mMaxIntervalNorm);
    if (max != 0)
        mBaseM = max;
    else
        mBaseM = 1;
    if (mBaseM > mGlobalM)
        mGlobalM = mBaseM;
}

int optimizercore::OptimizerAlgorithmNested::UpdateRanks(
    const std::set<OptimizerNestedTrialPoint>& localStorage, bool isLocal) {
    double dx, curr_rank, mu1 = -HUGE_VAL, localM = mBaseM;
    double localMConsts[3];

    for (int i = 0; i < mNumberOfThreads; i++)
        mIntervalsForTrials[i].rank = -HUGE_VAL;

    auto leftIt = localStorage.begin();
    auto rightIt = localStorage.begin();
    ++rightIt;

    int storageSize = localStorage.size();

    for (int j = 0; j < storageSize - 1; j++) {
        dx = rightIt->x[0] - leftIt->x[0];

        if (dx == 0)
            return 1;

        if (mLocalTuningMode != LocalTuningMode::None) {
            std::set<OptimizerNestedTrialPoint>::iterator rightRightIt = rightIt;

            if (j > 0 && j < storageSize - 2) {
                ++rightRightIt;

                std::swap(localMConsts[0], localMConsts[1]);
                std::swap(localMConsts[1], localMConsts[2]);

                localMConsts[2] =
                    fabs((rightRightIt->val - rightIt->val) / (rightRightIt->x[0] - rightIt->x[0]));

                mu1 = fmax(fmax(localMConsts[0], localMConsts[1]), localMConsts[2]);
            } else if (j == 0) {
                ++rightRightIt;

                localMConsts[1] = fabs((rightIt->val - leftIt->val) / dx);
                localMConsts[2] =
                    fabs((rightRightIt->val - rightIt->val) / (rightRightIt->x[0] - rightIt->x[0]));
                mu1 = fmax(localMConsts[1], localMConsts[2]);
            } else
                mu1 = fmax(localMConsts[1], localMConsts[2]);

            double mu2 = mBaseM * dx / mMaxIntervalNorm;

            if (mLocalTuningMode == LocalTuningMode::Maximum) {
                localM = fmax(localMConsts[1], fmax(0.5 * (mu1 + mu2), 0.001));
            } else {
                // LocalTuningMode::Adaptive

                // localM = fmax(mu1*(1 - dx / mMaxIntervalNorm) + mu2, 0.01);

                localM = fmax(localMConsts[1], fmax(mu1 / r + (r - 1) * mu2 / r, 0.001));
                // localM = fmax(mu1*mMConvolution + (1 - mMConvolution)*mu2, 0.01);
                // localM = fmax(mu1 / r + (1 - 1 / r)*mBaseM, 0.01);
                // if (mu1 < 0 || mu2 < 0)
                //	throw - 1;
                // printf(" %e  %e ||", mu1, mu2);
            }
        }

        curr_rank = dx + Pow2((rightIt->val - leftIt->val) / (r * localM)) / dx -
                    2 * (rightIt->val + leftIt->val - 2 * mZ) / (r * localM);
        if (isLocal)
            curr_rank /=
                sqrt((rightIt->val - mZ) * (leftIt->val - mZ)) / localM + pow(1.5, -mAlpha);

        if (curr_rank > mIntervalsForTrials[mNumberOfThreads - 1].rank) {
            OptimaizerNestedInterval newInterval(OptimizerNestedTrialPoint(*leftIt),
                                                 OptimizerNestedTrialPoint(*rightIt), curr_rank,
                                                 localM);
            for (int i = 0; i < mNumberOfThreads; i++)
                if (mIntervalsForTrials[i].rank < newInterval.rank)
                    std::swap(mIntervalsForTrials[i], newInterval);
        }
        ++leftIt;
        ++rightIt;
    }
    return 0;
}

bool optimizercore::OptimizerAlgorithmNested::InsertNewTrials(
    int trialsNumber, std::set<OptimizerNestedTrialPoint>& localStorage) {
    bool storageInsertionError;
    for (int i = 0; i < trialsNumber; i++) {
        auto insertionResult = localStorage.insert(mNextTrialsPoints[i]);

        if (!(storageInsertionError = insertionResult.second))
            break;

        UpdateGlobalM(insertionResult.first, localStorage);
    }
    return storageInsertionError;
}

OptimizerSolution optimizercore::OptimizerAlgorithmNested::DoLocalVerification(
    OptimizerSolution startSolution) {
    OptimizerFunctionPtr* functions = new OptimizerFunctionPtr[1];
    functions[0] = mTargetFunctionSmartPtr;

    OptimizerTask localTask(std::shared_ptr<OptimizerFunctionPtr>(
                                functions, utils::array_deleter<OptimizerFunctionPtr>()),
                            0, mMethodDimension, mSpaceTransform.GetLeftDomainBound(),
                            mSpaceTransform.GetRightDomainBound());

    localoptimizer::HookeJeevesLocalMethod localMethod;
    localMethod.SetEps(eps / 100);
    localMethod.SetInitialStep(2 * eps);
    localMethod.SetProblem(localTask);
    localMethod.SetStepMultiplier(2);
    localMethod.SetStartPoint(startSolution.GetOptimumPoint().get(), localTask.GetTaskDimension());

    SharedVector localOptimum(new double[mMethodDimension], array_deleter<double>());
    localMethod.StartOptimization(localOptimum.get());
    double bestLocalValue = mTargetFunction->Calculate(localOptimum.get());

    if (startSolution.GetOptimumValue() > bestLocalValue)
        return OptimizerSolution(startSolution.GetIterationsCount(), bestLocalValue, 0.5,
                                 mMethodDimension, localOptimum);

    return startSolution;
}

void optimizercore::OptimizerAlgorithmNested::SetTask(OptimizerFunctionPtr function,
                                                      OptimizerSpaceTransformation spaceTransform) {
    assert(function);

    mTargetFunctionSmartPtr = function;
    mTargetFunction = function.get();
    mSpaceTransform = spaceTransform;

    mIsTaskInitialized = true;
}

void optimizercore::OptimizerAlgorithmNested::SetThreadsNum(int num) {
    if (num > 0 && num < 100) {
        if (mNextPoints != nullptr)
            utils::DeleteMatrix(mNextPoints, mNumberOfThreads);
        mNumberOfThreads = num;
        if (mNextTrialsPoints)
            delete[] mNextTrialsPoints;
        mNextTrialsPoints = new OptimizerNestedTrialPoint[num];
        for (int j = 0; j < num; ++j) {
            for (int i = 0; i < mMethodDimension; ++i) {
                mNextTrialsPoints[j].x.resize(mMethodDimension);
            }
        }
        if (mIntervalsForTrials)
            delete[] mIntervalsForTrials;
        mIntervalsForTrials = new OptimaizerNestedInterval[num];
        mGlobalIterationsNumber = 0;
        mNextPoints = utils::AllocateMatrix<double>(mNumberOfThreads, mMethodDimension);
    }
}

void optimizercore::OptimizerAlgorithmNested::SetParameters(OptimizerParameters params) {
    assert(params.algDimension);
    assert(params.eps > 0);
    assert(params.localAlgStartIterationNumber > 0);
    assert(params.mapTightness > 5 && params.mapTightness <= 20);
    assert(params.maxIterationsNumber > 0);
    assert(params.localMixParameter >= 0 && params.localMixParameter <= 20);
    assert(params.r != nullptr);
    assert(params.numberOfThreads > 0);
    assert(params.reserves != nullptr);
    // assert(params.adaptiveLocalTuningParameter >= 0 &&
    //	params.adaptiveLocalTuningParameter <= 1);

    mLocalStartIterationNumber = params.localAlgStartIterationNumber;
    eps = params.eps;
    if (params.localMixParameter <= 10) {
        mLocalMixParameter = params.localMixParameter;
        mLocalMixType = true;
    } else {
        mLocalMixParameter = 20 - params.localMixParameter;
        mLocalMixType = false;
    }
    mNeedLocalVerification = params.localVerification;
    mAlpha = params.localExponent;
    mMethodDimension = params.algDimension;
    mMapTightness = params.mapTightness;
    mMapType = static_cast<int>(params.mapType);
    mMaxNumberOfIterations = params.maxIterationsNumber;
    mLocalTuningMode = params.localTuningMode;
    r = *params.r;
    if (mNextPoints)
        utils::DeleteMatrix(mNextPoints, mNumberOfThreads);
    mNextPoints = utils::AllocateMatrix<double>(mNumberOfThreads, mMethodDimension);
    this->SetThreadsNum(params.numberOfThreads);

    mIsParamsInitialized = true;

    mGlobalIterationsNumber = 0;
}

OptimizerResult optimizercore::OptimizerAlgorithmNested::StartOptimization(
    const double* xOpt, StopCriterionType stopType) {
    assert(mIsParamsInitialized && mIsTaskInitialized);
    assert(mSpaceTransform.GetDomainDimension() == mMethodDimension);
    InitializeInformationStorage();
    size_t iterationsCount = 0;
    mGlobalIterationsNumber = 0;
    int ranksUpdateErrCode;
    bool stop = false;
    std::set<OptimizerNestedTrialPoint> localStorage;

    // Preparation

    for (int i = 0; i < mMethodDimension; ++i)
        mNextTrialsPoints[0].x[i] = mSpaceTransform.GetLeftDomainBound().get()[i];
    IndexOprimization(1, 0);
    localStorage.insert(mNextTrialsPoints[0]);

    for (int i = 0; i < mMethodDimension; ++i)
        mNextTrialsPoints[0].x[i] = mSpaceTransform.GetRightDomainBound().get()[i];
    IndexOprimization(1, 0);
    localStorage.insert(mNextTrialsPoints[0]);

    for (int i = 1; i <= mNumberOfThreads; ++i) {
        mNextTrialsPoints[i - 1].x[0] = mSpaceTransform.GetLeftDomainBound().get()[0] +
                                        i * (mSpaceTransform.GetRightDomainBound().get()[0] -
                                             mSpaceTransform.GetLeftDomainBound().get()[0]) /
                                            (mNumberOfThreads + 1);
    }
    while (mGlobalIterationsNumber < mMaxNumberOfIterations && !stop) {
        iterationsCount++;

        //#pragma omp parallel for num_threads(mNumberOfThreads)
        for (int i = 0; i < mNumberOfThreads; i++) {
            IndexOprimization(1, i);

            //#pragma omp critical
            if (mNextTrialsPoints[i].val < mZ)
                mZ = mNextTrialsPoints[i].val;
            if (stopType == StopCriterionType::OptimalPoint) {
                if (NormNDimMax(mNextTrialsPoints[i].x.data(), xOpt, mMethodDimension) < eps) {
                    stop = true;
                    mOptimumEvaluation = mNextTrialsPoints[i];
                }
            }
        }

        if (!InsertNewTrials(mNumberOfThreads, localStorage))
            break;

        if (stop)
            break;

        if (iterationsCount >= mLocalStartIterationNumber) {
            if (iterationsCount % (12 - mLocalMixParameter) == 0 && mLocalMixParameter > 0)
                ranksUpdateErrCode = UpdateRanks(
                    localStorage,
                    mLocalMixType);  // Alex: Is there any point to store ranksUpdateErrCode and
                                     // don't do anything with it?
            else
                ranksUpdateErrCode = UpdateRanks(localStorage, !mLocalMixType);
        } else
            ranksUpdateErrCode = UpdateRanks(localStorage, false);

        for (int i = 0; i < mNumberOfThreads && !stop; i++) {
            OptimizerNestedTrialPoint left = mIntervalsForTrials[i].left;
            OptimizerNestedTrialPoint right = mIntervalsForTrials[i].right;
            mNextTrialsPoints[i].x[0] =
                (left.x[0] + right.x[0]) / 2 -
                sgn(right.val - left.val) *
                    (fabs(right.val - left.val) / mIntervalsForTrials[i].localM) / (2 * r);

            if (stopType != StopCriterionType::OptimalPoint) {
                if (fabs(right.x[0] - left.x[0]) < eps) {
                    stop = true;
                    mOptimumEvaluation = mNextTrialsPoints[i];
                }
            }
        }
    }
    if (mGlobalIterationsNumber < mMaxNumberOfIterations) {
        mNextTrialsPoints[0].x[0] = mOptimumEvaluation.x[0];
        IndexOprimization(1, 0);
        mOptimumEvaluation.val = mNextTrialsPoints[0].val;
        mSearchInformationStorage.insert(mNextTrialsPoints[0]);
    }
    for (auto& el : localStorage)
        mSearchInformationStorage.emplace(el);
    if (stopType == StopCriterionType::Precision ||
        mGlobalIterationsNumber >= mMaxNumberOfIterations) {
        mOptimumEvaluation =
            *std::min_element(mSearchInformationStorage.begin(), mSearchInformationStorage.cend(),
                              [](const OptimizerNestedTrialPoint& p1,
                                 const OptimizerNestedTrialPoint& p2) { return p1.val < p2.val; });
    }
    SharedVector optPoint(new double[mMethodDimension], array_deleter<double>());
    std::memcpy(optPoint.get(), mOptimumEvaluation.x.data(), mMethodDimension * sizeof(double));

    OptimizerSolution solution(mSearchInformationStorage.size(), mOptimumEvaluation.val, 0.5,
                               mMethodDimension, optPoint);

    if (mNeedLocalVerification)
        return OptimizerResult(DoLocalVerification(solution));
    else
        return OptimizerResult(solution);
}

void optimizercore::OptimizerAlgorithmNested::IndexOprimization(int index, int thread_id) {
    if (index >= mMethodDimension) {
        //#pragma omp critical
        { ++mGlobalIterationsNumber; }
        mNextTrialsPoints[thread_id].val =
            mTargetFunction->Calculate(mNextTrialsPoints[thread_id].x.data());
        return;
    }
    std::vector<OptimizerNestedTrialPoint> localStorage;
    std::vector<double> lb(mNextTrialsPoints[thread_id].x), rb(mNextTrialsPoints[thread_id].x);

    mNextTrialsPoints[thread_id].x[index] = mSpaceTransform.GetLeftDomainBound().get()[index];
    IndexOprimization(index + 1, thread_id);
    lb = mNextTrialsPoints[thread_id].x;
    localStorage.push_back(mNextTrialsPoints[thread_id]);

    mNextTrialsPoints[thread_id].x[index] = mSpaceTransform.GetRightDomainBound().get()[index];
    IndexOprimization(index + 1, thread_id);
    rb = mNextTrialsPoints[thread_id].x;
    localStorage.push_back(mNextTrialsPoints[thread_id]);

    double M = 0;
    size_t k = 2;
    size_t t = 0;
    M = abs((localStorage[1].val - localStorage[0].val) /
            (localStorage[1].x[index] - localStorage[0].x[index]));
    for (; ((localStorage[t + 1].x[index] - localStorage[t].x[index]) >= eps) &&
           mGlobalIterationsNumber < mMaxNumberOfIterations;
         ++k) {
        for (size_t i = 0; i < (k - 1u); ++i) {
            double M_tmp = abs((localStorage[i + 1].val - localStorage[i].val) /
                               (localStorage[i + 1].x[index] - localStorage[i].x[index]));
            if (M_tmp > M)
                M = M_tmp;
        }

        double m = 1;
        if (M != 0)
            m = r * M;
        if (m > mGlobalM)
            mGlobalM = m;
        t = 0;
        double R = m * (localStorage[1].x[index] - localStorage[0].x[index]) +
                   (pow((localStorage[1].val - localStorage[0].val), 2) /
                    (m * (localStorage[1].x[index] - localStorage[0].x[index]))) -
                   2 * (localStorage[1].val + localStorage[0].val);
        for (size_t i = 1; i < (k - 1u); ++i) {
            double R_tmp = m * (localStorage[i + 1].x[index] - localStorage[i].x[index]) +
                           (pow((localStorage[i + 1].val - localStorage[i].val), 2) /
                            (m * (localStorage[i + 1].x[index] - localStorage[i].x[index]))) -
                           2 * (localStorage[i + 1].val + localStorage[i].val);
            if (R_tmp > R) {
                t = i;
                R = R_tmp;
            }
        }

        lb[index] = mNextTrialsPoints[thread_id].x[index] =
            (localStorage[t].x[index] + localStorage[t + 1].x[index]) / 2 - (localStorage[t + 1].val - localStorage[t].val) / (2 * m);
        IndexOprimization(index + 1, thread_id);

        localStorage.insert(localStorage.begin() + t + 1, mNextTrialsPoints[thread_id]);
    }
    //#pragma omp critical
    {
        auto min = localStorage[t + 1];
        for (int i = 0; i < localStorage.size(); ++i) {
            if (localStorage[i].val < min.val) {
                min = localStorage[i];
            }
            mSearchInformationStorage.emplace(localStorage[i]);
        }
        mNextTrialsPoints[thread_id] = min;
    }
}

double optimizercore::OptimizerAlgorithmNested::GetLipschitzConst() const {
    return mGlobalM;
}

OptimazerNestedSearchSequence optimizercore::OptimizerAlgorithmNested::GetSearchSequence() const {
    return OptimazerNestedSearchSequence(mSearchInformationStorage, mMethodDimension);
}

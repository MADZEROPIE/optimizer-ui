#include "OptimizerAlgorithmAdaptive.h"
#include "HookeJeevesLocalMethod.hpp"

#include <cassert>
#include <algorithm>
#include <string>

using namespace optimizercore;
using namespace optimizercore::utils;

// ------- SubTask -------

optimizercore::OptimizerAlgorithmAdaptive::SubTask::SubTask(int _level, int _parent_id,
                                                            OptimizerNestedTrialPoint _basepoint) {
    level = _level;
    parent_id = _parent_id;
    basepoint = _basepoint;
    R = -INFINITY;
    m = 1;
    M = 0;
}

void optimizercore::OptimizerAlgorithmAdaptive::SubTask::clear() {
    // for (const XSub& xsub:trials) {
    //    SubTask* task = xsub.subtask;
    //    task->clear();
    //    delete task;
    //}
    trials.clear();
    // parent = nullptr;
    R = -INFINITY;
    m = 1;
    M = 0;
    basepoint.val = INFINITY;
}

// ------- OptimizerAlgorithmAdaptive -------

void optimizercore::OptimizerAlgorithmAdaptive::UpdateParents(int trial_id) {
    if (trial_id < 0)
        return;
    ITask* task = &all_trials[trial_id];
    while (task->parent_id != -1) {
        if (task->basepoint.val < all_tasks[task->parent_id].basepoint.val) {
            all_tasks[task->parent_id].basepoint = task->basepoint;
            // CalculateM(static_cast<SubTask*>(task->parent));
            // CalculateRanks(static_cast<SubTask*>(task->parent));
        }

        task = &all_tasks[task->parent_id];
    }
}

void optimizercore::OptimizerAlgorithmAdaptive::CalculateM(int task_id) {
    if (all_tasks[task_id].trials.size() <= 1) {
        all_tasks[task_id].M = 0;
        all_tasks[task_id].m = 1;
        return;
    }
    all_tasks[task_id].minIntervalNorm = INFINITY;
    double max = 0;
    all_tasks[task_id].M = 0;
    all_tasks[task_id].m = 0;
    auto it2 = all_tasks[task_id].trials.cbegin();
    auto it1 = it2++;
    int level = all_tasks[task_id].level;
    while (it2 != all_tasks[task_id].trials.cend()) {
        double mtpm = 0;
        double dx = it2->x - it1->x;
        if (dx < 0)
            throw "smth bad";
        if (dx < all_tasks[task_id].minIntervalNorm)
            all_tasks[task_id].minIntervalNorm = dx;
        if (level + 1 == mMethodDimension)
            mtpm = abs((all_trials[it1->subtask_id].basepoint.val - all_trials[it2->subtask_id].basepoint.val) / dx);
        else
            mtpm = abs((all_tasks[it1->subtask_id].basepoint.val - all_tasks[it2->subtask_id].basepoint.val) / dx);
        if (mtpm > max)
            max = mtpm;
        ++it1;
        ++it2;
    }
    if (max == 0)
        all_tasks[task_id].m = 1;
    else
        all_tasks[task_id].m = max * r;
    all_tasks[task_id].M = max;
    if (all_tasks[task_id].m > mLevelM[level])
        mLevelM[level] = all_tasks[task_id].m;
    if (all_tasks[task_id].m > mGlobalM)
        mGlobalM = all_tasks[task_id].m;
    if (all_tasks[task_id].minIntervalNorm > mMaxIntervalNorm)
        mMaxIntervalNorm = all_tasks[task_id].minIntervalNorm;
}

void optimizercore::OptimizerAlgorithmAdaptive::CalculateRanks(int task_id) {
    SubTask& task = all_tasks[task_id];
    if (task.trials.size() < 1)
        throw "No trials in task " + std::to_string(task_id);  // return;
    auto it2 = task.trials.begin();
    auto it1 = it2++;

    int t = 0;
    int level = task.level;
    double m = Choosem(task_id, mLipMode);

    double lx = mSpaceTransform.GetLeftDomainBound().get()[level];
    double rx = mSpaceTransform.GetRightDomainBound().get()[level];
    double zl;
    double zr;
    if (level + 1 != mMethodDimension)
        zr = all_tasks[it1->subtask_id].basepoint.val;
    else
        zr = all_trials[it1->subtask_id].basepoint.val;
    if (mIndexZ == IndexMethodOptions::None)
        task.R = 2 * m * (it1->x - lx) - 4 * zr;
    else if (mIndexZ == IndexMethodOptions::Global)
        task.R = 2 * (it1->x - lx) - 4 * (zr - all_tasks[0].basepoint.val) / m;
    else
        task.R = 2 * (it1->x - lx) - 4 * (zr - all_tasks[task_id].basepoint.val) / m;
    task.Rind = 0;
    while (it2 != task.trials.end()) {
        ++t;

        if (level + 1 != mMethodDimension) {
            zl = all_tasks[it1->subtask_id].basepoint.val;
            zr = all_tasks[it2->subtask_id].basepoint.val;
        } else {
            zl = all_trials[it1->subtask_id].basepoint.val;
            zr = all_trials[it2->subtask_id].basepoint.val;
        }
        double rtpm;
        double del = (it2->x - it1->x);
        if (mIndexZ == IndexMethodOptions::None)
            rtpm = m * del + (zr - zl) * (zr - zl) / (m * del) - 2 * (zr + zl);
        else if (mIndexZ == IndexMethodOptions::Global)
            rtpm = del + (zr - zl) * (zr - zl) / (m * m * del) - 2 * (zr + zl - 2 * all_tasks[0].basepoint.val) / m;
        else
            rtpm =
                del + (zr - zl) * (zr - zl) / (m * m * del) - 2 * (zr + zl - 2 * all_tasks[task_id].basepoint.val) / m;
        if (rtpm > task.R) {
            task.R = rtpm;
            task.Rind = t;
        }
        ++it1;
        ++it2;
    }
    double rtpm;

    if (level + 1 != mMethodDimension)
        zl = all_tasks[it1->subtask_id].basepoint.val;
    else
        zl = all_trials[it1->subtask_id].basepoint.val;
    if (mIndexZ == IndexMethodOptions::None)
        rtpm = 2 * m * (rx - it1->x) - 4 * zl;
    else if (mIndexZ == IndexMethodOptions::Global)
        rtpm = 2 * (rx - it1->x) - 4 * (zl - all_tasks[0].basepoint.val) / m;
    else
        rtpm = 2 * (rx - it1->x) - 4 * (zl - all_tasks[task_id].basepoint.val) / m;
    if (rtpm > task.R) {
        task.R = rtpm;
        task.Rind = t + 1;
    }
}

int optimizercore::OptimizerAlgorithmAdaptive::ChooseSubtask() {
    // Reset M
    mGlobalM = 0;
    for (int i = 0; i < mLevelM.size(); ++i) {
        mLevelM[i] = 0;
    }

    // Reset mMaxIntervalNorm
    mMaxIntervalNorm = 0;
    // Calculate m
    for (int i = 0; i < all_tasks.size(); ++i) {
        CalculateM(i);
    }

    // Check M
    for (int i = 0; i < mLevelM.size(); ++i) {
        if (mLevelM[i] == 0)
            mLevelM[i] = 1;
    }
    if (mGlobalM == 0)
        mGlobalM = 1;

    // Calculate Ranks
    int best = 0;
    CalculateRanks(best);
    for (int i = 1; i < all_tasks.size(); ++i) {
        CalculateRanks(i);
        if (all_tasks[i].R > all_tasks[best].R) {
            best = i;
        }
    }
    return best;
}

void optimizercore::OptimizerAlgorithmAdaptive::GenerateSubTasks(int parent_id, OptimizerNestedTrialPoint npnt) {
    // Iterative

    int level = all_tasks[parent_id].level + 1;
    bool setted = false;
    while (level < mMethodDimension) {
        if (!setted || mNewPNT == NewPointOptions::Half) {

            if (mNewPNT == NewPointOptions::Half || all_tasks[parent_id].trials.size() < 2)
                npnt.x[level] = (mSpaceTransform.GetRightDomainBound().get()[level] +
                                 mSpaceTransform.GetLeftDomainBound().get()[level]) /
                                2;
            else {
                auto tmp = std::upper_bound(all_tasks[parent_id].trials.begin(), all_tasks[parent_id].trials.end(),
                                            XSub(npnt.x[level - 1], -1));
                if (tmp == all_tasks[parent_id].trials.begin() || tmp == all_tasks[parent_id].trials.end())
                    npnt.x[level] = (mSpaceTransform.GetRightDomainBound().get()[level] +
                                     mSpaceTransform.GetLeftDomainBound().get()[level]) /
                                    2;
                else {
                    auto tmp2 = tmp--;
                    for (int j = level; j < mMethodDimension; ++j) {
                        npnt.x[j] =
                            all_tasks[tmp->subtask_id].basepoint.x[j] +
                            (all_tasks[tmp2->subtask_id].basepoint.x[j] - all_tasks[tmp->subtask_id].basepoint.x[j]) *
                                ((npnt.x[j - 1] - tmp->x) / (tmp2->x - tmp->x));
                    }
                    setted = true;
                }
            }
        }
        all_tasks.push_back(SubTask(level, parent_id, npnt));
        all_tasks[parent_id].trials.emplace(XSub(npnt.x[level - 1], all_tasks.size() - 1));
        parent_id = all_tasks.size() - 1;
        ++level;
    }

    npnt.val = mTargetFunction->Calculate(npnt.x.data());
    ITask newtrial(mMethodDimension, parent_id, npnt);
    all_trials.push_back(newtrial);
    all_tasks[parent_id].trials.insert(XSub(npnt.x[all_tasks[parent_id].level], all_trials.size() - 1));
    if (all_tasks[parent_id].basepoint.val >= npnt.val) {
        all_tasks[parent_id].basepoint = npnt;
    }
    UpdateParents(all_trials.size() - 1);

    mSearchInformationStorage.insert(npnt);

    // Recursive
    /*
    if ((all_tasks[parent_id].level + 1) == mMethodDimension) {
        npnt.val = mTargetFunction->Calculate(npnt.x.data());
        ITask newtrial(mMethodDimension, parent_id, npnt);
        all_trials.push_back(newtrial);
        all_tasks[parent_id].trials.insert(XSub(npnt.x[all_tasks[parent_id].level], all_trials.size() - 1));
        if (all_tasks[parent_id].basepoint.val >= npnt.val) {
            all_tasks[parent_id].basepoint = npnt;
        }
        UpdateParents(all_trials.size() - 1);

        mSearchInformationStorage.insert(npnt);

        return;
    }

    int level = all_tasks[parent_id].level + 1;
    if (mNewPNT == NewPointOptions::Half || all_tasks[parent_id].trials.size() < 2)
        npnt.x[level] = (mSpaceTransform.GetRightDomainBound().get()[level] +
    mSpaceTransform.GetLeftDomainBound().get()[level]) / 2; else { auto tmp =
    std::upper_bound(all_tasks[parent_id].trials.begin(), all_tasks[parent_id].trials.end(), XSub(npnt.x[level - 1],
    -1)); if (tmp == all_tasks[parent_id].trials.begin() || tmp == all_tasks[parent_id].trials.end()) {
            // double xtmp = (mSpaceTransform.GetRightDomainBound().get()[level] +
    mSpaceTransform.GetLeftDomainBound().get()[level]) / 2; npnt.x[level] =
    (mSpaceTransform.GetRightDomainBound().get()[level] + mSpaceTransform.GetLeftDomainBound().get()[level]) / 2;
        }
        else {
            auto tmp2 = tmp--;
            npnt.x[level] = all_tasks[tmp->subtask_id].basepoint.x[level] +
                (all_tasks[tmp2->subtask_id].basepoint.x[level] - all_tasks[tmp->subtask_id].basepoint.x[level])
                * ((npnt.x[level - 1] - tmp->x) / (tmp2->x - tmp->x));
        }
    }
    all_tasks.push_back(SubTask(level, parent_id, npnt));
    all_tasks[parent_id].trials.emplace(XSub(npnt.x[level - 1], all_tasks.size() - 1));

    return GenerateSubTasks(all_tasks.size() - 1, npnt);
    */
}

double optimizercore::OptimizerAlgorithmAdaptive::Choosem(int task_id, LipschitzConstantEvaluation mtype) {
    double m;
    if (mLipMode == LipschitzConstantEvaluation::Global)
        m = mGlobalM;  // task->m;
    else if (mLipMode == LipschitzConstantEvaluation::Single_task)
        m = all_tasks[task_id].m;
    else if (mLipMode == LipschitzConstantEvaluation::Level)
        m = mLevelM[all_tasks[task_id].level];
    else if (mLipMode == LipschitzConstantEvaluation::Adaptive) {
        if (all_tasks[task_id].trials.size() <= 1)
            m = mGlobalM;
        else {
            double MG = mGlobalM * all_tasks[task_id].minIntervalNorm / mMaxIntervalNorm;
            if (MG > all_tasks[task_id].m) {
                m = MG;
                ++mGlobalCount;
            } else {
                m = all_tasks[task_id].m;
                ++mLocalCount;
            }
        }
    } else
        throw "IDK";
    return m;
}

optimizercore::OptimizerAlgorithmAdaptive::OptimizerAlgorithmAdaptive() {
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

optimizercore::OptimizerAlgorithmAdaptive::~OptimizerAlgorithmAdaptive() {
}

void optimizercore::OptimizerAlgorithmAdaptive::AllocMem() {
}

void optimizercore::OptimizerAlgorithmAdaptive::InitializeInformationStorage() {
    if (!mIsAlgorithmMemoryAllocated) {
        AllocMem();
        mIsAlgorithmMemoryAllocated = true;
    }

    mZ = HUGE_VAL;
    mGlobalM = 1;
    mMaxIntervalNorm = 0;

    mLocalCount = 0;
    mGlobalCount = 0;

    mSearchInformationStorage.clear();
    all_tasks.clear();
    all_trials.clear();
}

OptimizerSolution optimizercore::OptimizerAlgorithmAdaptive::DoLocalVerification(OptimizerSolution startSolution) {
    OptimizerFunctionPtr* functions = new OptimizerFunctionPtr[1];
    functions[0] = mTargetFunctionSmartPtr;

    OptimizerTask localTask(
        std::shared_ptr<OptimizerFunctionPtr>(functions, utils::array_deleter<OptimizerFunctionPtr>()), 0,
        mMethodDimension, mSpaceTransform.GetLeftDomainBound(), mSpaceTransform.GetRightDomainBound());

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
        return OptimizerSolution(startSolution.GetIterationsCount(), bestLocalValue, 0.5, mMethodDimension,
                                 localOptimum);

    return startSolution;
}

void optimizercore::OptimizerAlgorithmAdaptive::SetTask(OptimizerFunctionPtr function,
                                                        OptimizerSpaceTransformation spaceTransform) {
    assert(function);

    mTargetFunctionSmartPtr = function;
    mTargetFunction = function.get();
    mSpaceTransform = spaceTransform;

    mIsTaskInitialized = true;
}

void optimizercore::OptimizerAlgorithmAdaptive::SetThreadsNum(int num) {
    // INFO: NO PARALLEL REALIZATION AT THAT MOMENT.
}

void optimizercore::OptimizerAlgorithmAdaptive::SetParameters(OptimizerParameters params) {
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
    mLipMode = params.lipEval;
    mIndexZ = params.indexZ;
    mNewPNT = params.newPNT;
    r = *params.r;
    // if (mNextPoints)
    //    utils::DeleteMatrix(mNextPoints, mNumberOfThreads);
    // mNextPoints = utils::AllocateMatrix<double>(mNumberOfThreads, mMethodDimension);
    this->SetThreadsNum(params.numberOfThreads);

    mIsParamsInitialized = true;

    mGlobalIterationsNumber = 0;

    mLevelM.resize(mMethodDimension);
}

OptimizerResult optimizercore::OptimizerAlgorithmAdaptive::StartOptimization(const double* xOpt,
                                                                             StopCriterionType stopType) {
    assert(mIsParamsInitialized && mIsTaskInitialized);
    assert(mSpaceTransform.GetDomainDimension() == mMethodDimension);
    InitializeInformationStorage();
    size_t iterationsCount = 0;
    mGlobalIterationsNumber = 0;

    OptimizerNestedTrialPoint pnt1(mMethodDimension);
    pnt1.x[0] = (mSpaceTransform.GetRightDomainBound().get()[0] + mSpaceTransform.GetLeftDomainBound().get()[0]) / 2;
    pnt1.val = INFINITY;
    all_tasks.push_back(SubTask(0, -1, pnt1));

    GenerateSubTasks(0, all_tasks[0].basepoint);
    bool stop = false;
    while (!stop && iterationsCount < mMaxNumberOfIterations) {
        int task_id = ChooseSubtask();
        SubTask& task = all_tasks[task_id];
        int level = task.level;
        double m = Choosem(task_id, mLipMode);

        // CHOOSE NEW POINT
        double newx;
        if (task.Rind == 0) {
            newx = (mSpaceTransform.GetLeftDomainBound().get()[level] + task.trials.begin()->x) / 2;
        } else if (task.Rind == task.trials.size()) {
            auto itmp = task.trials.end();
            --itmp;
            newx = (mSpaceTransform.GetRightDomainBound().get()[level] + itmp->x) / 2;
        } else {
            int t = task.Rind;
            int i = 0;
            auto itl = task.trials.begin();
            while (i < t) {
                ++itl;
                ++i;
            }  // NONSENSE. CHANGE SET TO VECTOR AND USE SORT OR SMART INSERT
            auto itr = itl--;
            if (level + 1 != mMethodDimension)
                newx = (itl->x + itr->x) / 2 -
                       (all_tasks[itr->subtask_id].basepoint.val - all_tasks[itl->subtask_id].basepoint.val) / (2 * m);
            else
                newx =
                    (itl->x + itr->x) / 2 -
                    (all_trials[itr->subtask_id].basepoint.val - all_trials[itl->subtask_id].basepoint.val) / (2 * m);
        }

        // Make new trial
        OptimizerNestedTrialPoint pnt(task.basepoint);
        // pnt = task.basepoint;
        pnt.val = INFINITY;
        pnt.x[level] = newx;
        GenerateSubTasks(task_id, pnt);
        ++iterationsCount;

        if (stopType == StopCriterionType::OptimalPoint) {
            stop = NormNDimMax(all_tasks[0].basepoint.x.data(), xOpt, mMethodDimension) < eps;
        } else {
            auto base_it2 = all_tasks[0].trials.cbegin();
            auto base_it = base_it2++;
            while (base_it2 != all_tasks[0].trials.cend() && !stop) {
                // stop = (base_it2->x - base_it->x < eps);
                if (all_tasks[base_it->subtask_id].basepoint.val < all_tasks[0].basepoint.val)
                    throw "Update parents(?) not workin' properly";  // Debug check.
                stop = NormNDimMax(all_tasks[base_it2->subtask_id].basepoint.x.data(),
                                   all_tasks[base_it->subtask_id].basepoint.x.data(), mMethodDimension) < eps;
                ++base_it2;
                ++base_it;
            }
        }
    }
    SharedVector optPoint(new double[mMethodDimension], array_deleter<double>());
    std::memcpy(optPoint.get(), all_tasks[0].basepoint.x.data(), mMethodDimension * sizeof(double));
    OptimizerSolution solution(iterationsCount, all_tasks[0].basepoint.val, 0, mMethodDimension, optPoint);
    if (mNeedLocalVerification)
        return OptimizerResult(DoLocalVerification(solution));
    else
        return OptimizerResult(solution);
}

double optimizercore::OptimizerAlgorithmAdaptive::GetLipschitzConst() {
    // TODO: DELETE THIS. CALCULATE M AFTER LAST TRIAL IS DONE.
    for (int i = 0; i < all_tasks.size(); ++i) {
        this->CalculateM(i);
    }

    return mGlobalM / r;
}

uint64_t optimizercore::OptimizerAlgorithmAdaptive::GetCountLocalM() const {
    return mLocalCount;
}

uint64_t optimizercore::OptimizerAlgorithmAdaptive::GetCountGlobalM() const {
    return mGlobalCount;
}

OptimazerNestedSearchSequence optimizercore::OptimizerAlgorithmAdaptive::GetSearchSequence() const {
    // std::set<OptimizerNestedTrialPoint> trials;
    // TODO: ����������� ����� � ������ ��� ���������� ���������. ��� ��������� ����� � ���������� �� �����.

    return OptimazerNestedSearchSequence(mSearchInformationStorage, mMethodDimension);
}

optimizercore::OptimizerAlgorithmAdaptive::XSub::XSub(double _x, int _subtask) {
    x = _x;
    subtask_id = _subtask;
}

optimizercore::OptimizerAlgorithmAdaptive::ITask::ITask(int _level, int _parent_id,
                                                        OptimizerNestedTrialPoint _basepoint) {
    level = _level;
    parent_id = _parent_id;
    basepoint = _basepoint;
}

#include "OptimizerAlgorithmAdaptive.h"
#include "HookeJeevesLocalMethod.hpp"

#include <cassert>
#include <algorithm>

using namespace optimizercore;
using namespace optimizercore::utils;

// ------- SubTask -------

optimizercore::OptimizerAlgorithmAdaptive::SubTask::SubTask(int _level, ITask* _parent, OptimizerNestedTrialPoint _basepoint)
{
    level = _level;
    parent = _parent;
    basepoint = _basepoint;
    R = -INFINITY;
    m = 1;
    M = 0;
}

void optimizercore::OptimizerAlgorithmAdaptive::SubTask::clear()
{
    //for (const XSub& xsub:trials) {
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

void optimizercore::OptimizerAlgorithmAdaptive::UpdateParents(ITask* task)
{
    while (task->parent != nullptr) {
        if (task->basepoint.val <= task->parent->basepoint.val) {
            task->parent->basepoint = task->basepoint;
            //CalculateM(static_cast<SubTask*>(task->parent));
            //CalculateRanks(static_cast<SubTask*>(task->parent));
        }

        task = task->parent;
    }
}

void optimizercore::OptimizerAlgorithmAdaptive::CalculateM(SubTask* task)
{
    if (task->trials.size() <= 1) { 
        task->M = 0;
        task->m = 1;
        return;
    }
    double max = 0;
    auto it2 = task->trials.begin();
    auto it1 = it2++;
    while (it2 != task->trials.cend()) {
        double mtpm = abs(it1->subtask->basepoint.val - it2->subtask->basepoint.val) / (it2->x - it1->x);
        if (mtpm > max) max = mtpm;
        ++it1; ++it2;
    }
    if (max == 0) task->m = 1;
    else task->m = max * r;
    task->M = max;

}

void optimizercore::OptimizerAlgorithmAdaptive::CalculateRanks(SubTask* task)
{
    if (task->trials.size() < 1) return;
    auto it2 = task->trials.begin();
    auto it1 = it2++;

    
    int t = 0;
    double m = task->m;
    int level = task->level;
    double lx = mSpaceTransform.GetLeftDomainBound().get()[level];
    double rx = mSpaceTransform.GetRightDomainBound().get()[level];
    task->R = 2* m * (it1->x - lx) - 4 * it1->subtask->basepoint.val;
    task->Rind = 0;
    while (it2 != task->trials.end()) {
        ++t;
        double zl = it1->subtask->basepoint.val;
        double zr = it2->subtask->basepoint.val;
        double rtpm = m * (it2->x - it1->x) + (zr-zl)*(zr-zl)/(m * (it2->x - it1->x)) - 2 * (zr + zl);
        if (rtpm > task->R) {
            task->R = rtpm;
            task->Rind = t;
        }
        ++it1; ++it2;
    }
    double rtpm = 2 * m * (rx - it1->x) - 4 * it1->subtask->basepoint.val;
    if (rtpm > task->R) {
        task->R = rtpm;
        task->Rind = t+1;
    }

}

OptimizerAlgorithmAdaptive::SubTask* optimizercore::OptimizerAlgorithmAdaptive::ChooseSubtask()
{
    SubTask* best = base_task;
    CalculateM(static_cast<SubTask*>(best));
    CalculateRanks(static_cast<SubTask*>(best));
    for (int i = 1; i < all_tasks.size();++i) {
        CalculateM(static_cast<SubTask*>(all_tasks[i]));
        CalculateRanks(static_cast<SubTask*>(all_tasks[i]));
        if (all_tasks[i]->R > best->R) {
            best = all_tasks[i];
        }
    }
    return best;
}

void optimizercore::OptimizerAlgorithmAdaptive::GenerateSubTasks(SubTask* parent, OptimizerNestedTrialPoint npnt)
{
    if (parent->level+1 == mMethodDimention) {
        npnt.val = mTargetFunction->Calculate(npnt.x.data());
        ITask* newtrial = new ITask(mMethodDimention, parent, npnt);
        
        parent->trials.insert(XSub(npnt.x[parent->level], newtrial));
        if (parent->basepoint.val >= npnt.val) {
            parent->basepoint = npnt;
            UpdateParents(newtrial);
        }

        
        mSearchInformationStorage.insert(npnt);
        all_trials.push_back(newtrial);
        return;
    }
    
    int level = parent->level + 1;
    npnt.x[level] = (mSpaceTransform.GetRightDomainBound().get()[level] + mSpaceTransform.GetLeftDomainBound().get()[level])/2;
    SubTask* task = new SubTask(level, parent, npnt);
    parent->trials.insert(XSub(npnt.x[parent->level], task));
    all_tasks.push_back(task);
    return GenerateSubTasks(task, npnt);
}

optimizercore::OptimizerAlgorithmAdaptive::OptimizerAlgorithmAdaptive()
{
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

optimizercore::OptimizerAlgorithmAdaptive::~OptimizerAlgorithmAdaptive()
{
    //if (base_task != nullptr) base_task->clear();
    //delete base_task;
    for (SubTask* task : all_tasks) {
        delete task;
    }
    for (ITask* trial : all_trials) {
        delete trial;
    }

}

void optimizercore::OptimizerAlgorithmAdaptive::AllocMem()
{
}

void optimizercore::OptimizerAlgorithmAdaptive::InitializeInformationStorage()
{
    if (!mIsAlgorithmMemoryAllocated) {
        AllocMem();
        mIsAlgorithmMemoryAllocated = true;
    }

    mZ = HUGE_VAL;
    mGlobalM = 1;
    mMaxIntervalNorm = 0;

    mSearchInformationStorage.clear();

}

OptimizerSolution optimizercore::OptimizerAlgorithmAdaptive::DoLocalVerification(OptimizerSolution startSolution)
{
    OptimizerFunctionPtr* functions = new OptimizerFunctionPtr[1];
    functions[0] = mTargetFunctionSmartPtr;

    OptimizerTask localTask(std::shared_ptr<OptimizerFunctionPtr>(functions,
        utils::array_deleter<OptimizerFunctionPtr>()),
        0, mMethodDimention, mSpaceTransform.GetLeftDomainBound(),
        mSpaceTransform.GetRightDomainBound());

    localoptimizer::HookeJeevesLocalMethod localMethod;
    localMethod.SetEps(eps / 100);
    localMethod.SetInitialStep(2 * eps);
    localMethod.SetProblem(localTask);
    localMethod.SetStepMultiplier(2);
    localMethod.SetStartPoint(startSolution.GetOptimumPoint().get(),
        localTask.GetTaskDimention());

    SharedVector localOptimum(new double[mMethodDimention], array_deleter<double>());
    localMethod.StartOptimization(localOptimum.get());
    double bestLocalValue = mTargetFunction->Calculate(localOptimum.get());

    if (startSolution.GetOptimumValue() > bestLocalValue)
        return OptimizerSolution(startSolution.GetIterationsCount(),
            bestLocalValue, 0.5, mMethodDimention, localOptimum);

    return startSolution;
}





void optimizercore::OptimizerAlgorithmAdaptive::SetTask(OptimizerFunctionPtr function, OptimizerSpaceTransformation spaceTransform)
{
    assert(function);

    mTargetFunctionSmartPtr = function;
    mTargetFunction = function.get();
    mSpaceTransform = spaceTransform;

    mIsTaskInitialized = true;
}

void optimizercore::OptimizerAlgorithmAdaptive::SetThreadsNum(int num)
{
    // INFO: NO PARALLEL REALIZATION AT THAT MOMENT.
}

void optimizercore::OptimizerAlgorithmAdaptive::SetParameters(OptimizerParameters params)
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

    mGlobalIterationsNumber = 0;
}

OptimizerResult optimizercore::OptimizerAlgorithmAdaptive::StartOptimization(const double* xOpt, StopCriterionType stopType)
{
    assert(mIsParamsInitialized && mIsTaskInitialized);
    assert(mSpaceTransform.GetDomainDimention() == mMethodDimention);
    InitializeInformationStorage();
    size_t iterationsCount = 0;
    mGlobalIterationsNumber = 0;

    OptimizerNestedTrialPoint pnt(mMethodDimention);
    pnt.x[0] = (mSpaceTransform.GetRightDomainBound().get()[0] + mSpaceTransform.GetLeftDomainBound().get()[0]) / 2;
    pnt.val = INFINITY;
    base_task = new SubTask(0, nullptr, pnt);
    all_tasks.push_back(base_task);
    GenerateSubTasks(base_task, base_task->basepoint);
    while (NormNDimMax(base_task->basepoint.x.data(), xOpt, mMethodDimention) >= eps && iterationsCount < mMaxNumberOfIterations) {
        SubTask* task = ChooseSubtask();
        int level = task->level;
        double m = task->m;

        // CHOOSE NEW POINT
        double newx;
        if (task->Rind == 0) {
            newx = (mSpaceTransform.GetLeftDomainBound().get()[level] + task->trials.begin()->x) / 2;
        }
        else if (task->Rind == task->trials.size()) {
            auto itmp = task->trials.end();
            --itmp;
            newx = (mSpaceTransform.GetRightDomainBound().get()[level] + itmp->x) / 2;
        }
        else {
            int t = task->Rind;
            int i = 0;
            auto itl = task->trials.begin();
            while (i < t) { ++itl; ++i; } // BULLSHIT. CHANGE SET TO VECTOR AND USE SORT OR SMART INSERT
            auto itr = itl--;
            newx = (itl->x + itr->x) / 2 - (itr->subtask->basepoint.val - itl->subtask->basepoint.val) / (2 * m);
        }

        // Make new trial
        pnt = task->basepoint;
        pnt.val = INFINITY;
        pnt.x[level] = newx;
        GenerateSubTasks(task, pnt);
        ++iterationsCount;
    }
    SharedVector optPoint(new double[mMethodDimention], array_deleter<double>());
    std::memcpy(optPoint.get(), base_task->basepoint.x.data(), mMethodDimention * sizeof(double));
    OptimizerSolution solution(iterationsCount, base_task->basepoint.val, 0, mMethodDimention, optPoint);
    if (mNeedLocalVerification)
        return OptimizerResult(DoLocalVerification(solution));
    else
        return OptimizerResult(solution);
}

double optimizercore::OptimizerAlgorithmAdaptive::GetLipschitzConst() const
{
    /*if (base_task != nullptr)*/ return base_task->M;
    //return 0.0;
}

OptimazerNestedSearchSequence optimizercore::OptimizerAlgorithmAdaptive::GetSearchSequence() const
{
    // std::set<OptimizerNestedTrialPoint> trials;
    // TODO: Реализовать поиск в ширину для добавления испытаний. Или поступить умнее и записывать их сразу.

    return OptimazerNestedSearchSequence(mSearchInformationStorage, mMethodDimention);
}

optimizercore::OptimizerAlgorithmAdaptive::XSub::XSub(double _x, ITask* _subtask)
{
    x = _x;
    subtask = _subtask;
}

optimizercore::OptimizerAlgorithmAdaptive::ITask::ITask(int _level, ITask* _parent, OptimizerNestedTrialPoint _basepoint)
{
    level = _level;
    parent = _parent;
    basepoint = _basepoint;
}

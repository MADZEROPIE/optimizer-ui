#include "OptimizerAlgorithmAdaptive.h"
#include "HookeJeevesLocalMethod.hpp"

#include <cassert>
#include <algorithm>
#include <string>
#include <stdexcept>

using namespace optimizercore;
using namespace optimizercore::utils;

// ------- SubTask -------

optimizercore::OptimizerAlgorithmAdaptive::SubTask::SubTask(int _level, int _parent_id,
                                                            OptimizerNestedTrialPoint _basepoint) {
    level = _level;
    parent_id = _parent_id;
    basepoint = _basepoint;
    maxpoint = _basepoint.val;
    R = -INFINITY;
    m = m_trans = 1;
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
    m = m_trans = 1;

    basepoint.val = INFINITY;
    transval = INFINITY;
    maxpoint = -INFINITY;
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
        if (task->maxpoint > all_tasks[task->parent_id].maxpoint) {
            all_tasks[task->parent_id].maxpoint = task->maxpoint;
        }

        task = &all_tasks[task->parent_id];
    }
}

void optimizercore::OptimizerAlgorithmAdaptive::CalculateM(int task_id, bool mon) {
    if (all_tasks[task_id].trials.size() <= 1) {
        all_tasks[task_id].m = all_tasks[task_id].m_trans = 1;
        return;
    }
    all_tasks[task_id].minIntervalNorm = INFINITY;
    double max = 0;
    if (!mon)
        all_tasks[task_id].m = 0;
    else
        all_tasks[task_id].m_trans = 0;
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
        double zl, zr;
        //if (level + 1 == mMethodDimension) {
        //    zl = all_trials[it1->subtask_id].transval;  //.basepoint.val;
        //    zr = all_trials[it2->subtask_id].transval;  //.basepoint.val;
        //} else {
        //    zl = all_tasks[it1->subtask_id].transval;  //.basepoint.val;
        //    zr = all_tasks[it2->subtask_id].transval;  //.basepoint.val;
        //}
        zl = GetValue(it1->subtask_id, level + 1 == mMethodDimension, mon);
        zr = GetValue(it2->subtask_id, level + 1 == mMethodDimension, mon); 
        // if (mMonotonous == MonotonousOptions::Monotonous) {
        //    MonotonousTransform(zl, task_id);
        //    MonotonousTransform(zr, task_id);
        //}
        mtpm = abs((zr - zl) / dx);
        if (mtpm > max)
            max = mtpm;
        ++it1;
        ++it2;
    }
    if (max == 0) {
        max = 1;
    } else {
        max = max * r;
    }
    
    //if (all_tasks[task_id].m > mLevelM[level])
    //    mLevelM[level] = all_tasks[task_id].m;
    //if (all_tasks[task_id].m > mGlobalM)
    //    mGlobalM = all_tasks[task_id].m;
    UpdateM(task_id, max, mon);
    if (all_tasks[task_id].minIntervalNorm > mMaxIntervalNorm)
        mMaxIntervalNorm = all_tasks[task_id].minIntervalNorm;
}

void optimizercore::OptimizerAlgorithmAdaptive::CalculateRanks(int task_id, bool mon) {
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

    zr = GetValue(it1->subtask_id, level + 1 == mMethodDimension, mon); 
    //if (mMonotonous == MonotonousOptions::Monotonous) {
    //    MonotonousTransform(zr, task_id);
    //}

    double* R;
    if (!mon) {
        R = &task.R;
    } else {
        R = &task.R_trans;
    }

    if (mIndexZ == IndexMethodOptions::None) {
        *R = 2 * m * (it1->x - lx) - 4 * zr;
    } else if (mIndexZ == IndexMethodOptions::Global) {
        *R = 2 * (it1->x - lx) - 4 * (zr - all_tasks[0].basepoint.val) / m;
    } else {
        *R = 2 * (it1->x - lx) - 4 * (zr - all_tasks[task_id].basepoint.val) / m;
    }
    if (!mon)
        task.Rind = 0;
    else
        task.Rtrind = 0;
    while (it2 != task.trials.end()) {
        ++t;

        //if (level + 1 != mMethodDimension) {
        //    zl = all_tasks[it1->subtask_id].transval;  //.basepoint.val;
        //    zr = all_tasks[it2->subtask_id].transval;  //.basepoint.val;
        //} else {
        //    zl = all_trials[it1->subtask_id].transval;  //.basepoint.val;
        //    zr = all_trials[it2->subtask_id].transval;  //.basepoint.val;
        //}
        zl = GetValue(it1->subtask_id, level + 1 == mMethodDimension, mon); 
        zr = GetValue(it2->subtask_id, level + 1 == mMethodDimension, mon); 
        //if (mMonotonous == MonotonousOptions::Monotonous) {
        //    MonotonousTransform(zl, task_id);
        //    MonotonousTransform(zr, task_id);
        //}
        double rtpm;
        double del = (it2->x - it1->x);
        if (mIndexZ == IndexMethodOptions::None) {
            rtpm = m * del + (zr - zl) * (zr - zl) / (m * del) - 2 * (zr + zl);
        } else if (mIndexZ == IndexMethodOptions::Global) {
            rtpm = del + (zr - zl) * (zr - zl) / (m * m * del) - 2 * (zr + zl - 2 * all_tasks[0].basepoint.val) / m;
        } else {
            rtpm =
                del + (zr - zl) * (zr - zl) / (m * m * del) - 2 * (zr + zl - 2 * all_tasks[task_id].basepoint.val) / m;
        }

        if (!mon && rtpm > task.R) {
            task.R = rtpm;
            task.Rind = t;
        } else if (mon && rtpm > task.R_trans) {
            task.R_trans = rtpm;
            task.Rtrind = t;
        }
        ++it1;
        ++it2;
    }
    double rtpm;

    //if (level + 1 != mMethodDimension) {
    //    zl = all_tasks[it1->subtask_id].transval;  // basepoint.val;
    //} else {
    //    zl = all_trials[it1->subtask_id].transval;  // basepoint.val;
    //}
    //if (mMonotonous == MonotonousOptions::Monotonous) {
    //    MonotonousTransform(zl, task_id);
    //}

    zl = GetValue(it1->subtask_id, level + 1 == mMethodDimension, mon);

    if (mIndexZ == IndexMethodOptions::None) {
        rtpm = 2 * m * (rx - it1->x) - 4 * zl;
    } else if (mIndexZ == IndexMethodOptions::Global) {
        rtpm = 2 * (rx - it1->x) - 4 * (zl - all_tasks[0].basepoint.val) / m;
    } else {
        rtpm = 2 * (rx - it1->x) - 4 * (zl - all_tasks[task_id].basepoint.val) / m;
    }
    if (!mon && rtpm > task.R) {
        task.R = rtpm;
        task.Rind = t + 1;
    } else if (mon && rtpm > task.R_trans) {
        task.R_trans = rtpm;
        task.Rtrind = t + 1;
    }
}

int optimizercore::OptimizerAlgorithmAdaptive::ChooseSubtask() {
    int best = 0;
    //CalculateRanks(best, false);
    for (int i = 1; i < all_tasks.size(); ++i) {
        //CalculateRanks(i, false);
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
        all_tasks.back().maxpoint = -INFINITY;
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
    if (all_tasks[parent_id].maxpoint < npnt.val) {
        all_tasks[parent_id].maxpoint = npnt.val;
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

double optimizercore::OptimizerAlgorithmAdaptive::Choosem(int task_id, LipschitzConstantEvaluation mtype, bool mon) {
    double taskm, glm, lvlm;
    if (!mon) {
        taskm = all_tasks[task_id].m;
        glm = mGlobalM;
        lvlm = mLevelM[all_tasks[task_id].level];
    } else {
        taskm = all_tasks[task_id].m_trans;
        glm = mGlobalMTrans;
        lvlm = mLevelMTrans[all_tasks[task_id].level];
    }
    double m;
    if (mLipMode == LipschitzConstantEvaluation::Global) {
        m = glm;  // task->m;
    } else if (mLipMode == LipschitzConstantEvaluation::Single_task) {
        m = taskm;
    } else if (mLipMode == LipschitzConstantEvaluation::Level) {
        m = lvlm;
    } else if (mLipMode == LipschitzConstantEvaluation::Adaptive) {
        if (all_tasks[task_id].trials.size() <= 1)
            m = glm;
        else {
            double MG = glm * all_tasks[task_id].minIntervalNorm / mMaxIntervalNorm;
            if (MG > taskm) {
                m = MG;
                ++mGlobalCount;
            } else {
                m = taskm;
                ++mLocalCount;
            }
        }
    } else
        throw std::runtime_error("IDK");
    return m;
}

void optimizercore::OptimizerAlgorithmAdaptive::MonotonousTransformAll(int task_id) {
    SubTask& task = all_tasks[task_id];
    int level = task.level;
    for (auto& trial : task.trials) {
        double* z;
        if (level + 1 != mMethodDimension) {
            all_tasks[trial.subtask_id].transval = all_tasks[trial.subtask_id].basepoint.val;
            z = &all_tasks[trial.subtask_id].transval;
        } else {
            all_trials[trial.subtask_id].transval = all_trials[trial.subtask_id].basepoint.val;
            z = &all_trials[trial.subtask_id].transval;
        }
        MonotonousTransform(*z, task_id);
    }
    
}

void optimizercore::OptimizerAlgorithmAdaptive::MonotonousTransform(double& z, int task_id) {
    if (this->mIndexZ != IndexMethodOptions::None || all_tasks[task_id].trials.size()<2 || mMonotonous==MonotonousOptions::None) {
        return;
    }
    double minz = all_tasks[0].basepoint.val;
    //double maxz = all_tasks[0].maxpoint;
    //if ((maxz - minz) < 1e-6) {
    //    return;
    //}
    //double u;

    //if (z > maxz) {
    //    throw "WTF";
    //}

    //if ((maxz - z) < 1e-6) {
    //    u = 1;
    //} else {
    //    u = (z - minz) / (maxz - minz);
    //}
    //z = sqrt(1 - pow(1 - u, 2));
    z = sqrt(z - minz);
}

double optimizercore::OptimizerAlgorithmAdaptive::GetValue(int subtask_id, bool from_trial, bool mon) {
    if (from_trial) {
        if (mon) {
            return all_trials[subtask_id].transval;
        }
        return all_trials[subtask_id].basepoint.val;
    }

    if (mon) {
        return all_tasks[subtask_id].transval;
    }
    return all_tasks[subtask_id].basepoint.val;
}

void optimizercore::OptimizerAlgorithmAdaptive::UpdateM(int task_id, double m, bool mon) {
    const auto& level = all_tasks[task_id].level;
    if (!mon) {
        all_tasks[task_id].m = m;
        if (all_tasks[task_id].m > mLevelM[level])
            mLevelM[level] = all_tasks[task_id].m;
        if (all_tasks[task_id].m > mGlobalM)
            mGlobalM = all_tasks[task_id].m;
    } else {
        all_tasks[task_id].m_trans = m;
        if (all_tasks[task_id].m_trans > mLevelMTrans[level])
            mLevelMTrans[level] = all_tasks[task_id].m_trans;
        if (all_tasks[task_id].m_trans > mGlobalMTrans)
            mGlobalMTrans = all_tasks[task_id].m_trans;
    }
}

void optimizercore::OptimizerAlgorithmAdaptive::RecalcAll() {
    // Transform values
    //if (mMonotonous == MonotonousOptions::Monotonous) {
        // #pragma omp parallel for num_threads(mNumberOfThreads)
        for (int i = 0; i < all_tasks.size(); ++i) {
            MonotonousTransformAll(i);
        }
    //}
    // Reset M
    mGlobalM = mGlobalMTrans = 0;
    for (int i = 0; i < mLevelM.size(); ++i) {
        mLevelM[i] = mLevelMTrans[i] = 0;
    }

    // Reset mMaxIntervalNorm
    mMaxIntervalNorm = 0;
    // Calculate m
    for (int i = 0; i < all_tasks.size(); ++i) {
        CalculateM(i, false);
        if (mMonotonous == MonotonousOptions::Monotonous) {
            CalculateM(i, true);
        }
    }

    // Check M
    for (int i = 0; i < mLevelM.size(); ++i) {
        if (mLevelM[i] == 0)
            mLevelM[i] = 1;
        if (mLevelMTrans[i] == 0)
            mLevelMTrans[i] = 1;
    }
    if (mGlobalM == 0) {
        mGlobalM = 1;
    }
    if (mGlobalMTrans == 0) {
        mGlobalMTrans = 1;
    }

    // Calculate Ranks
    for (int i = 0; i < all_tasks.size(); ++i) {
        CalculateRanks(i, false);
        if (mMonotonous == MonotonousOptions::Monotonous) {
            CalculateRanks(i, true);
        }
    }
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
    mNumberOfThreads = num;
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
    mMonotonous = params.monotonous;
    if (mIndexZ != IndexMethodOptions::None) {
        mMonotonous = MonotonousOptions::None;
    }
    r = *params.r;
    // if (mNextPoints)
    //    utils::DeleteMatrix(mNextPoints, mNumberOfThreads);
    // mNextPoints = utils::AllocateMatrix<double>(mNumberOfThreads, mMethodDimension);
    this->SetThreadsNum(params.numberOfThreads);

    mIsParamsInitialized = true;

    mGlobalIterationsNumber = 0;

    mLevelM.resize(mMethodDimension);
    mLevelMTrans.resize(mMethodDimension);
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
    all_tasks[0].maxpoint = -INFINITY;

    GenerateSubTasks(0, all_tasks[0].basepoint);
    bool stop = false;
    while (!stop && iterationsCount < mMaxNumberOfIterations) {
        RecalcAll();
        int task_id = ChooseSubtask();
        SubTask& task = all_tasks[task_id];
        int level = task.level;
        double m = Choosem(task_id, mLipMode, mMonotonous == MonotonousOptions::Monotonous);
        bool is_mon = mMonotonous == MonotonousOptions::Monotonous;
        // CHOOSE NEW POINT
        double newx;
        if ((!is_mon && task.Rind == 0) || (is_mon && task.Rtrind == 0)) {
            newx = (mSpaceTransform.GetLeftDomainBound().get()[level] + task.trials.begin()->x) / 2;
        } else if ((!is_mon && task.Rind == task.trials.size()) || (is_mon && task.Rtrind == task.trials.size())) {
            auto itmp = task.trials.end();
            --itmp;
            newx = (mSpaceTransform.GetRightDomainBound().get()[level] + itmp->x) / 2;
        } else {
            int t = mMonotonous == MonotonousOptions::Monotonous ? task.Rtrind: task.Rind;
            int i = 0;
            auto itl = task.trials.begin();
            // std::advance(itl, t);
            while (i < t) {
                ++itl;
                ++i;
            }  // NONSENSE. CHANGE SET TO VECTOR AND USE SORT OR SMART INSERT
            auto itr = itl--;
            double zr, zl;
            //if (level + 1 != mMethodDimension) {
            //    //zr = all_tasks[itr->subtask_id].basepoint.val;
            //   // zl = all_tasks[itl->subtask_id].basepoint.val;
            //    zr = all_tasks[itr->subtask_id].transval;
            //    zl = all_tasks[itl->subtask_id].transval;
            //} else {
            //   // zr = all_trials[itr->subtask_id].basepoint.val;
            //   // zl = all_trials[itl->subtask_id].basepoint.val;
            //   zr = all_trials[itr->subtask_id].transval;
            //   zl = all_trials[itl->subtask_id].transval;
            //}
            zr = GetValue(itr->subtask_id, level + 1 == mMethodDimension, mMonotonous == MonotonousOptions::Monotonous);
            zl = GetValue(itl->subtask_id, level + 1 == mMethodDimension, mMonotonous == MonotonousOptions::Monotonous);
            newx = (itl->x + itr->x) / 2 - (zr - zl) / (2 * m);

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
        MonotonousTransformAll(i);
    }
    mGlobalM = 0;
    for (int i = 0; i < all_tasks.size(); ++i) {
        this->CalculateM(i, false);
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
    // TODO: Реализовать поиск в ширину для добавления испытаний. Или поступить умнее и записывать их сразу.

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
    maxpoint = _basepoint.val;
    transval = _basepoint.val;
}

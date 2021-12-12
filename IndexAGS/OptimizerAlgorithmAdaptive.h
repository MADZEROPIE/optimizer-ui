#pragma once
#include "OptimizerCoreGlobal.hpp"
#include "OptimizerTask.hpp"
#include "OptimizerSolution.hpp"
#include "OptimizerFunction.hpp"
#include "OptimizerDataStructures.hpp"
#include "OptimizerSolution.hpp"
#include "OptimizerResult.hpp"
#include "OptimizerSearchSequence.hpp"
#include "OptimizerAlgorithmUnconstrained.hpp"

#include <set>

namespace optimizercore
{

    class EXPORT_API OptimizerAlgorithmAdaptive final: public IOptimazerAlgorithm
    {
	private:
		class XSub;
		class ITask {
		public:
			int level=0;
			ITask* parent = nullptr;
			OptimizerNestedTrialPoint basepoint;
			ITask(int _level=0, ITask* _parent=nullptr, OptimizerNestedTrialPoint _basepoint = OptimizerNestedTrialPoint());
		};
		class SubTask: public ITask {
		  public:
			double R = -INFINITY;
			double m = 1;
			double M = 0;
			int Rind = 0;

			  // also best point ?

			std::set<XSub> trials;
		  public:
			SubTask(int _level, ITask* _parent, OptimizerNestedTrialPoint _basepoint = OptimizerNestedTrialPoint());
			~SubTask() { /*clear(); */}
			void clear();
		};
		class XSub
		{
		public:
			double x;
			ITask* subtask;
			XSub(double _x, ITask* _subtask = nullptr);
			~XSub() = default;
			bool operator <(const XSub& b) const { return x < b.x; }

		};

    private:

		bool mLocalMixType;
		bool mIsAlgorithmMemoryAllocated;
		bool mIsParamsInitialized;
		bool mIsTaskInitialized;
		bool mNeedLocalVerification;

		int mNumberOfThreads;
		int mLocalStartIterationNumber;
		int mMaxNumberOfIterations;
		size_t mGlobalIterationsNumber = 0;

		int mMethodDimention;

		int mAlpha; //???
		int mLocalMixParameter;

		int mMapType;
		int mMapTightness;

		OptimizerSpaceTransformation mSpaceTransform;
		OptimizerFunction* mTargetFunction;
		OptimizerFunctionPtr mTargetFunctionSmartPtr;

		OptimaizerNestedInterval* mIntervalsForTrials;
		std::set<OptimizerNestedTrialPoint> mSearchInformationStorage;
		OptimizerNestedTrialPoint mOptimumEvaluation,* mNextTrialsPoints;

		LocalTuningMode mLocalTuningMode;

		double* leftDomainBound,* rightDomainBound;

		double mGlobalM, mZ, eps, r, mMaxIntervalNorm;
		double** mNextPoints;
		double* mLevelM;

		void AllocMem();
		void InitializeInformationStorage();
		OptimizerSolution DoLocalVerification(OptimizerSolution startPoint);

		SubTask* base_task;
		std::vector<SubTask*> all_tasks;  // Change to priority queue or smth

		// Also. Doesn't store points, so...
		std::vector<ITask*> all_trials;

		void UpdateParents(ITask* task);
		void CalculateM(SubTask* task);
		void CalculateRanks(SubTask* task);
		SubTask* ChooseSubtask();
		void GenerateSubTasks(SubTask* parent, OptimizerNestedTrialPoint npnt);
	public:
		OptimizerAlgorithmAdaptive();
		~OptimizerAlgorithmAdaptive();

		void SetTask(OptimizerFunctionPtr function,
			OptimizerSpaceTransformation spaceTransform);
		void SetThreadsNum(int num);
		void SetParameters(OptimizerParameters params);

		OptimizerResult StartOptimization(const double* xOpt,
			StopCriterionType stopType);

		double GetLipschitzConst() const;
		OptimazerNestedSearchSequence GetSearchSequence() const;

    };

}


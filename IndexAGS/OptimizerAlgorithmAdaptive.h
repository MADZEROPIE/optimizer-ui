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
			int level = 0;
			int parent_id = -1;
			OptimizerNestedTrialPoint basepoint;
			ITask(int _level = 0, int _parent_id = -1, OptimizerNestedTrialPoint _basepoint = OptimizerNestedTrialPoint());
		};
		class SubTask: public ITask {
		  public:
			double R = -INFINITY;
			double m = 1;
			double M = 0;
			double minIntervalNorm = INFINITY;
			int Rind = 0;
			// std::vector<SubTask*> subtasks;  // subtasks+basepoint and trials have same usability, so why store both?

			  // also best point ?

			std::set<XSub> trials;
		  public:
			SubTask(int _level, int _parent_id, OptimizerNestedTrialPoint _basepoint = OptimizerNestedTrialPoint());
			~SubTask() { /*clear(); */}
			void clear();
		};
		class XSub
		{
		public:
			double x;
			int subtask_id;
			XSub(double _x, int _subtask = -1);
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

		uint64_t mLocalCount;
		uint64_t mGlobalCount;

		OptimizerSpaceTransformation mSpaceTransform;
		OptimizerFunction* mTargetFunction;
		OptimizerFunctionPtr mTargetFunctionSmartPtr;

		OptimaizerNestedInterval* mIntervalsForTrials;
		std::set<OptimizerNestedTrialPoint> mSearchInformationStorage;
		OptimizerNestedTrialPoint mOptimumEvaluation,* mNextTrialsPoints;

		LocalTuningMode mLocalTuningMode;
		LipschitzConstantEvaluation mLipMode;
		IndexMethodOptions mIndexZ;
		NewPointOptions mNewPNT;

		double* leftDomainBound,* rightDomainBound;

		double mGlobalM, mZ, eps, r, mMaxIntervalNorm;
		double** mNextPoints;
		//double* mLevelM;

		void AllocMem();
		void InitializeInformationStorage();
		OptimizerSolution DoLocalVerification(OptimizerSolution startPoint);


		std::vector<SubTask> all_tasks;  // Change to priority queue or smth

		// Also. all_tasks Doesn't store points, so...
		std::vector<ITask> all_trials;
		std::vector<double> mLevelM;
		void UpdateParents(int trial_id);
		void CalculateM(int task_id);
		void CalculateRanks(int task_id);
		int ChooseSubtask();
		void GenerateSubTasks(int parent, OptimizerNestedTrialPoint npnt);
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
		uint64_t GetCountLocalM() const;
		uint64_t GetCountGlobalM() const;
		OptimazerNestedSearchSequence GetSearchSequence() const;

    };

}


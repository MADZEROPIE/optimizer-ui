#pragma once

#include "OptimizerCoreGlobal.hpp"
#include "OptimizerTask.hpp"
#include "OptimizerSolution.hpp"
#include "OptimizerFunction.hpp"
#include "OptimizerDataStructures.hpp"
#include "OptimizerSolution.hpp"
#include "OptimizerResult.hpp"
#include "OptimizerSearchSequence.hpp"

#include <set>

namespace optimizercore
{

	class EXPORT_API OptimizerAlgorithmNested final
	{

	private:

		bool mLocalMixType;
		bool mIsAlgorithmMemoryAllocated;
		bool mIsParamsInitialized;
		bool mIsTaskInitialized;
		bool mNeedLocalVerification;

		int mNumberOfThreads;
		int mLocalStartIterationNumber;
		int mMaxNumberOfIterations;

		int mMethodDimention;
		//int mAlpha; //???
		//int mLocalMixParameter;
		//int mMapType;

		//OptimizerSpaceTransformation mSpaceTransform;
		OptimizerFunction* mTargetFunction;
		//OptimizerFunctionPtr mTargetFunctionSmartPtr;

		OptimaizerInterval* mIntervalsForTrials;
        std::set<OptimizerNestedTrialPoint> mSearchInformationStorage;
        OptimizerNestedTrialPoint mOptimumEvaluation, *mNextTrialsPoints;

		LocalTuningMode mLocalTuningMode;

		double mGlobalM, mZ, eps, r, mMaxIntervalNorm;
		double** mNextPoints;

		void AllocMem();
		void InitializeInformationStorage();
		void UpdateGlobalM(std::set<OptimizerNestedTrialPoint>::iterator&);
		int UpdateRanks(bool isLocal);
		bool InsertNewTrials(int trialsNumber);
		OptimizerSolution DoLocalVerification(OptimizerSolution startPoint);

	public:
		OptimizerAlgorithmNested();
		~OptimizerAlgorithmNested();

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

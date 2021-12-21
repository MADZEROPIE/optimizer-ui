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

	class EXPORT_API OptimizerAlgorithmNested final : public IOptimazerAlgorithm
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
        OptimizerNestedTrialPoint mOptimumEvaluation, *mNextTrialsPoints;

		LocalTuningMode mLocalTuningMode;

		double* leftDomainBound, *rightDomainBound;

		double mBaseM, mZ, eps, r, mMaxIntervalNorm, mGlobalM;
		double** mNextPoints;

		void AllocMem();
		void InitializeInformationStorage();
		void UpdateGlobalM(std::set<OptimizerNestedTrialPoint>::iterator&, const std::set<OptimizerNestedTrialPoint>& localStorage);
		int UpdateRanks(const std::set<OptimizerNestedTrialPoint>& localStorage, bool isLocal);
		bool InsertNewTrials(int trialsNumber, std::set<OptimizerNestedTrialPoint>& localStorage);
		OptimizerSolution DoLocalVerification(OptimizerSolution startPoint);
		void IndexOprimization(int index, int thread_id);

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

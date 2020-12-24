#include "OptimizerSearchSequence.hpp"
#include "CoreUtils.hpp"
#include "OptimizerCoreGlobal.hpp"
#include "Map.h"
#include <cassert>

using namespace optimizercore;

OptimizerSearchSequence::OptimizerSearchSequence()
{
	mSize = 0;
	mDimention = 0;
	mMapDensity = 0;
	mMapType = MapType::Simple;
	mIsInitialized = false;
}
OptimizerSearchSequence::OptimizerSearchSequence(const std::set<OptimizerTrialPoint>& searchSequence,
	unsigned dimention, MapType mapType, unsigned mapDensity, OptimizerSpaceTransformation transform)
{
	assert(!searchSequence.empty());
	assert(dimention > 1);
	assert(mapDensity > 0);

	mSize = searchSequence.size();
	mDimention = dimention;
	mMapType = mapType;
	mMapDensity = mapDensity;
	mSpaceTransform = transform;

	mPointsMemPtr = new double[mSize];
	mValuesMemPtr = new double[mSize];

	auto seqIterator = searchSequence.begin();

	for (unsigned i = 0; i < mSize; i++)
	{
		mPointsMemPtr[i] = seqIterator->x;
		mValuesMemPtr[i] = seqIterator->val;
		++seqIterator;
	}

	mPoints = SharedVector(mPointsMemPtr, utils::array_deleter<double>());
	mValues = SharedVector(mValuesMemPtr, utils::array_deleter<double>());

	mIsInitialized = true;
}
OptimizerSearchSequence::~OptimizerSearchSequence()
{	}
size_t OptimizerSearchSequence::GetSize() const
{
	CheckIsInitialized();
	return mSize;
}
unsigned OptimizerSearchSequence::GetDimention() const
{
	CheckIsInitialized();
	return mDimention;
}
unsigned OptimizerSearchSequence::GetMapDensity() const
{
	CheckIsInitialized();
	return mMapDensity;
}
MapType OptimizerSearchSequence::GetMapType() const
{
	CheckIsInitialized();
	return mMapType;
}
void OptimizerSearchSequence::GetPoint(int index, double* x)
{
	mapd(mPointsMemPtr[index], mMapDensity, x, mDimention, static_cast<int> (mMapType));
	mSpaceTransform.Transform(x, x);
}
double OptimizerSearchSequence::GetOneDimPoint(int index)
{
	return mPointsMemPtr[index];
}
double OptimizerSearchSequence::GetValue(int index)
{
	mValuesMemPtr = mValues.get();
	return mValuesMemPtr[index];
}
void OptimizerSearchSequence::CheckIsInitialized() const
{
	if (mIsInitialized == false)
		throw std::exception("Optimizer Solution is not initialized.");
}
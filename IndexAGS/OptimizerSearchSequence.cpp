#include "OptimizerSearchSequence.hpp"
#include "CoreUtils.hpp"
#include "OptimizerCoreGlobal.hpp"
#include "Map.h"
#include <cassert>

using namespace optimizercore;

// --------------------- ISearchSequence -------------
size_t optimizercore::ISearchSequence::GetSize() const {
    return mSize;
};

// --------------- OptimizerSearchSequence ----------
OptimizerSearchSequence::OptimizerSearchSequence() {
    mSize = 0;
    mDimension = 0;
    mMapDensity = 0;
    mMapType = MapType::Simple;
    mIsInitialized = false;
    mPointsMemPtr = nullptr;
    mValuesMemPtr = nullptr;
}

OptimizerSearchSequence::OptimizerSearchSequence(const std::set<OptimizerTrialPoint>& searchSequence,
                                                 unsigned dimension, MapType mapType, unsigned mapDensity,
                                                 OptimizerSpaceTransformation transform) {
    assert(!searchSequence.empty());
    assert(dimension > 1);
    assert(mapDensity > 0);

    mSize = searchSequence.size();
    mDimension = dimension;
    mMapType = mapType;
    mMapDensity = mapDensity;
    mSpaceTransform = transform;

    mPointsMemPtr = new double[mSize];
    mValuesMemPtr = new double[mSize];

    auto seqIterator = searchSequence.begin();

    for (unsigned i = 0; i < mSize; i++) {
        mPointsMemPtr[i] = seqIterator->x;
        mValuesMemPtr[i] = seqIterator->val;
        ++seqIterator;
    }

    mPoints = SharedVector(mPointsMemPtr, utils::array_deleter<double>());
    mValues = SharedVector(mValuesMemPtr, utils::array_deleter<double>());

    mIsInitialized = true;
}

OptimizerSearchSequence::~OptimizerSearchSequence() {
}

unsigned OptimizerSearchSequence::GetDimension() const {
    CheckIsInitialized();
    return mDimension;
}

unsigned OptimizerSearchSequence::GetMapDensity() const {
    CheckIsInitialized();
    return mMapDensity;
}

MapType OptimizerSearchSequence::GetMapType() const {
    CheckIsInitialized();
    return mMapType;
}

void OptimizerSearchSequence::GetPoint(int index, double* x) {
    mapd(mPointsMemPtr[index], mMapDensity, x, mDimension, static_cast<int>(mMapType));
    mSpaceTransform.Transform(x, x);
}

double OptimizerSearchSequence::GetOneDimPoint(int index) {
    return mPointsMemPtr[index];
}

double OptimizerSearchSequence::GetValue(int index) {
    mValuesMemPtr = mValues.get();
    return mValuesMemPtr[index];
}

void OptimizerSearchSequence::CheckIsInitialized() const {
    if (mIsInitialized == false)
        throw std::exception("Optimizer Solution is not initialized.");
}

// --------- OptimazerNestedSearchSequence -------------\\


optimizercore::OptimazerNestedSearchSequence::OptimazerNestedSearchSequence() {
    mSize = 0;
    mDimension = 0;
    mMapDensity = 0;
    mMapType = MapType::Simple;
    mIsInitialized = false;
    mValuesMemPtr = nullptr;
}

optimizercore::OptimazerNestedSearchSequence::OptimazerNestedSearchSequence(
    const std::set<OptimizerNestedTrialPoint>& searchSequence, unsigned dimention) {
    mSize = searchSequence.size();
    mDimension = dimention;
    mPoints.resize(mSize);

    mValuesMemPtr = new double[mSize];
    auto seqIterator = searchSequence.begin();

    for (unsigned i = 0; i < mSize; i++) {
        mPoints[i] = seqIterator->x;
        mValuesMemPtr[i] = seqIterator->val;
        ++seqIterator;
    }
    mValues = SharedVector(mValuesMemPtr, utils::array_deleter<double>());

    mIsInitialized = true;
}

void optimizercore::OptimazerNestedSearchSequence::GetPoint(int indx, double* x) {
    if (indx < 0 || indx >= mSize) {
        throw "Incorrect index";
    }
    for (int i = 0; i < mDimension; ++i) {
        x[i] = mPoints[indx][i];
    }
}

double optimizercore::OptimazerNestedSearchSequence::GetOneDimPoint(int indx)  // ???
{
    // TODO: USE Y_to_x
    return 0.0;
}

double optimizercore::OptimazerNestedSearchSequence::GetValue(int indx) {
    mValuesMemPtr = mValues.get();
    return mValuesMemPtr[indx];
}

unsigned optimizercore::OptimazerNestedSearchSequence::GetMapDensity() const {
    CheckIsInitialized();
    return mMapDensity;
}

unsigned optimizercore::OptimazerNestedSearchSequence::GetDimension() const {
    CheckIsInitialized();
    return mDimension;
}

MapType optimizercore::OptimazerNestedSearchSequence::GetMapType() const {
    CheckIsInitialized();
    return mMapType;
}

void optimizercore::OptimazerNestedSearchSequence::CheckIsInitialized() const {
    if (mIsInitialized == false)
        throw std::exception("Optimizer Solution is not initialized.");
}

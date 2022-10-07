#ifndef OPTIMIZER_SEARCH_SEQUENCE_HPP
#define OPTIMIZER_SEARCH_SEQUENCE_HPP

#include "OptimizerCoreGlobal.hpp"
#include "OptimizerDataStructures.hpp"
#include "Map.h"
#include "OptimizerSpaceTransformation.hpp"
#include <set>

namespace optimizercore {

class EXPORT_API ISearchSequence {
protected:
    size_t mSize;

public:
    virtual size_t GetSize() const;
    virtual void GetPoint(int indx, double* x) = 0;
    virtual double GetOneDimPoint(int indx) = 0;
    virtual double GetValue(int indx) = 0;

    // TODO: Make them Non-virtual, because they are all the same...
    virtual unsigned GetMapDensity() const = 0;
    virtual unsigned GetDimension() const = 0;
    virtual MapType GetMapType() const = 0;
};

class EXPORT_API OptimizerSearchSequence final : public ISearchSequence {

private:
    unsigned mDimension;
    MapType mMapType;
    unsigned mMapDensity;
    double* mPointsMemPtr;
    double* mValuesMemPtr;
    SharedVector mPoints;
    SharedVector mValues;
    OptimizerSpaceTransformation mSpaceTransform;
    bool mIsInitialized;

public:
    unsigned GetMapDensity() const;
    unsigned GetDimension() const;
    MapType GetMapType() const;

    void GetPoint(int indx, double* x);
    double GetOneDimPoint(int indx);
    double GetValue(int indx);

    OptimizerSearchSequence();
    OptimizerSearchSequence(const std::set<OptimizerTrialPoint>& sequence, unsigned dimention, MapType mapType,
                            unsigned mapDensity, OptimizerSpaceTransformation transform);
    ~OptimizerSearchSequence();

private:
    void CheckIsInitialized() const;
};

class EXPORT_API OptimazerNestedSearchSequence final : public ISearchSequence {
private:
    unsigned mDimension;
    MapType mMapType;
    unsigned mMapDensity;
    double* mValuesMemPtr;
    std::vector<std::vector<double>> mPoints;  // TODO: change to shared_ptr<vector<double>>
    SharedVector mValues;
    OptimizerSpaceTransformation mSpaceTransform;
    bool mIsInitialized;

public:
    OptimazerNestedSearchSequence();
    OptimazerNestedSearchSequence(const std::set<OptimizerNestedTrialPoint>& sequence, unsigned dimention);
    void GetPoint(int indx, double* x);
    double GetOneDimPoint(int indx);
    double GetValue(int indx);

    virtual unsigned GetMapDensity() const;
    virtual unsigned GetDimension() const;
    virtual MapType GetMapType() const;

private:
    void CheckIsInitialized() const;
};

}  // namespace optimizercore
#endif
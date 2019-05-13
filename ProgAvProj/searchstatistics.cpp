#include "searchstatistics.h"
//--------------------------------------------------------------------------------------------------
SearchStatistics::SearchStatistics()
{
}
//--------------------------------------------------------------------------------------------------
void SearchStatistics::startSearchtime()
{
    _searchStartTime = QDateTime::currentMSecsSinceEpoch();
}
//--------------------------------------------------------------------------------------------------
void SearchStatistics::endSearchTime()
{
    _searchEndTime = QDateTime::currentMSecsSinceEpoch();
}
//--------------------------------------------------------------------------------------------------
void SearchStatistics::addNewPointVisited(const uint16_t newPoint)
{
    _visitedPoints.insert(newPoint);
}
//--------------------------------------------------------------------------------------------------
void SearchStatistics::addIter()
{
    _numIters++;
}
//--------------------------------------------------------------------------------------------------
void SearchStatistics::addNewPathCost(const uint64_t newCost)
{
    _pathCostsFound.push_back(newCost);
}
//--------------------------------------------------------------------------------------------------
void SearchStatistics::clear()
{
    _pathCostsFound.clear();
    _visitedPoints.clear();
    _numIters = 0;
    _searchStartTime = 0;
    _searchEndTime = 0;
}
//--------------------------------------------------------------------------------------------------
void SearchStatistics::setSearchMethodName(const std::string& newName)
{
    _searchMethod = newName;
}
//--------------------------------------------------------------------------------------------------
qint64 SearchStatistics::getSearchTotalTime() const
{
    return (((0 != _searchStartTime) && (0 != _searchEndTime)) ? (_searchEndTime - _searchStartTime) :
                                                                 0);
}
//--------------------------------------------------------------------------------------------------
qint64 SearchStatistics::getSearchTimeAfterStart() const
{
    return ((0 != _searchStartTime) ? (QDateTime::currentMSecsSinceEpoch() - _searchStartTime) :
                                      0);
}
//--------------------------------------------------------------------------------------------------
quint64 SearchStatistics::getNumIters() const
{
    return _numIters;
}
//--------------------------------------------------------------------------------------------------
void SearchStatistics::addSearchMethodName(const std::string& newSearch)
{
    _searchMethod = newSearch;
}
//--------------------------------------------------------------------------------------------------
const std::string& SearchStatistics::getSearchMethodName() const
{
    return _searchMethod;
}
//--------------------------------------------------------------------------------------------------
uint64_t SearchStatistics::getMaxPathCost() const
{
    const auto maxValIte{std::max_element(std::begin(_pathCostsFound), std::end(_pathCostsFound))};

    return ((maxValIte != _pathCostsFound.end()) ? *maxValIte : 0);
}
//--------------------------------------------------------------------------------------------------
uint64_t SearchStatistics::getMinPathCost() const
{
    const auto minValIte{std::min_element(std::begin(_pathCostsFound), std::end(_pathCostsFound))};

    return ((minValIte != _pathCostsFound.end()) ? *minValIte : 0);
}
//--------------------------------------------------------------------------------------------------
uint64_t SearchStatistics::getNumPathsFound() const
{
    return _pathCostsFound.size();
}
//--------------------------------------------------------------------------------------------------
uint64_t SearchStatistics::getMedPathCost() const
{
    return (_pathCostsFound.empty() ? 0 :
            std::accumulate(_pathCostsFound.begin(), _pathCostsFound.end(), 0)/_pathCostsFound.size());
}
//--------------------------------------------------------------------------------------------------

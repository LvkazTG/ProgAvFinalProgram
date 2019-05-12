#include "searchastart.h"

#include "mapaobj.h"

#include <QDebug>
//--------------------------------------------------------------------------------------------------
searchAStart::searchAStart(const MapaObj& map) : BaseSearch{map}, _mapInUse{&map}
{

}
//--------------------------------------------------------------------------------------------------
void searchAStart::initLoopConditions()
{
    // Dont need to check heuristic for first point
    const std::tuple<uint16_t, uint64_t, uint16_t>firstItem{_actualPath.begin()->getPointHash(), 0,
                                                            std::numeric_limits<uint16_t>::max()};
    _toCheckPoints.emplace(0, firstItem);
    _bestPathCost = std::numeric_limits<uint64_t>::max();

    //const auto extraCostAStar{calcHeuristicAStar(startPoint)};
}
//--------------------------------------------------------------------------------------------------
bool searchAStart::extraCoonditionLoopSearch() const
{
    // No extra conditional break of loop stipulated
    return true;
}
//--------------------------------------------------------------------------------------------------
void searchAStart::principalLoopSearch()
{
    bool forceNextIteration{false};

    if(!_toCheckPoints.empty())
    {
        const auto pointChecking{_toCheckPoints.extract(_toCheckPoints.begin())};
        const auto pointCheckingHash{std::get<0>(pointChecking.mapped())};

        _searchStats.addNewPointVisited(pointCheckingHash);

        const auto pointCheckingCost{std::get<1>(pointChecking.mapped())};

        const auto iterVisitedListPoint{_visitedPoints.find(pointCheckingHash)};

        if(!_bestPath.empty() && (_bestPathCost <= pointCheckingCost))
        {
            // If best route is already found and this point is more expensive, we cancel this iteration on start
            forceNextIteration = true;
        }


        else if(pointCheckingHash == _endHash)
        {
            if(_bestPathCost > pointCheckingCost)
            {
                // Add points to checked list
                const std::tuple<uint64_t, uint16_t> infoVisitedPoint{pointCheckingCost,
                                                                      std::get<2>(pointChecking.mapped())};
                _visitedPoints.emplace(pointCheckingHash, infoVisitedPoint);

                updateBestPath(pointCheckingHash, pointCheckingCost);
            }
            else
            {
                // Do nothinng
            }

            forceNextIteration = true;
        }
        else if(_visitedPoints.end() != iterVisitedListPoint)
        {
            if(std::get<1>(iterVisitedListPoint->second) <= std::get<1>(pointChecking.mapped()))
            {
                forceNextIteration = true;
            }
            else
            {
                // Its ok to continue iteration on this point
            }
        }
        else
        {
            // Visiting a point for the first time, keep iterating this point
        }

        if(!forceNextIteration)
        {
            for(const auto& singleConnInfo: _connMapList->getConnectedMapElem(pointCheckingHash))
            {
                const auto pointHash{singleConnInfo.first};
                const uint64_t newCost{singleConnInfo.second + std::get<1>(pointChecking.mapped())};

                if(!_bestPath.empty() && (_bestPathCost <= newCost))
                {
                    // If best route is already found and this point is more expensive, we wont add this item to list
                    continue;
                    //forceNextIteration = true;
                }

                if(_visitedPoints.end() != iterVisitedListPoint)
                {
                    if(std::get<0>(iterVisitedListPoint->second) < newCost)
                    {
                        // This iteration does not update list as point already has a best case
                        continue;
                    }
                    else
                    {
                        // Point will be redone later
//                        _visitedPoints.erase(iterVisitedListPoint);
                    }
                }

                const std::tuple<uint16_t, uint64_t, uint16_t> newItemOnList{pointHash, newCost,
                                                                             pointCheckingHash};

                const uint64_t costWithHeuristic{newCost + calcHeuristicAStar(pointHash)};
                _toCheckPoints.emplace(costWithHeuristic, newItemOnList);

            }
        }
        // Add itered point to visited list
        const std::tuple<uint64_t, uint16_t> infoVisitedPoint{std::get<1>(pointChecking.mapped()),
                                                              std::get<2>(pointChecking.mapped())};
        _visitedPoints.emplace(pointCheckingHash, infoVisitedPoint);
    }
    else
    {
        _keepSearchGoing = false;
    }

}
//--------------------------------------------------------------------------------------------------
uint64_t searchAStart::calcHeuristicAStar(const uint16_t pointHash) const
{
    return static_cast<uint64_t>(_mapInUse->getPoint(pointHash)->distFrom(*(_mapInUse->getPoint(_endHash))));
}
//--------------------------------------------------------------------------------------------------
void searchAStart::updateBestPath(const uint16_t lastPointHash, const uint64_t expectedTotalCost)
{
    // Should never fail
    Q_ASSERT(lastPointHash == _endHash);
//    _actualPath.emplace_back(newConnHash, _connMapList->getConnectedMapElem(newConnHash));
    auto addHash{lastPointHash};

    _bestPath.clear();
    while(addHash != _startHash)
    {
        _bestPath.emplace_front(addHash, _connMapList->getConnectedMapElem(addHash));

        // Get conn Last Hash

        addHash = std::get<1>(_visitedPoints.at(addHash));
    }

    // To add first elem
    _bestPath.emplace_front(_startHash, _connMapList->getConnectedMapElem(_startHash));

    uint64_t bestCostSum{0};

    for(auto iterSingleElem = _bestPath.begin() ; _bestPath.end() != iterSingleElem ; iterSingleElem++)
    {
        const auto iterNextElem{std::next(iterSingleElem)};

        if(iterNextElem == _bestPath.end())
        {
            break;
        }

        const bool foundHash{iterSingleElem->moveUntilFind(iterNextElem->getPointHash(), true)};

        // Should never fail
        Q_ASSERT(foundHash);

        bestCostSum += iterSingleElem->getActualConnCost();
    }

    // Should never fail
//    Q_ASSERT(expectedTotalCost == bestCostSum);
    if(expectedTotalCost != bestCostSum)
    {
        qDebug() << "BUAAAAAAAAAAAAAAAAAAA ------------ Contamos errado!!!!!" << expectedTotalCost << bestCostSum;
    }

    _bestPathCost = expectedTotalCost;
}
//--------------------------------------------------------------------------------------------------

#include "searchgraphplanadapt.h"

#include <algorithm>

#include "pointobj.h"

#include <QDebug>
//--------------------------------------------------------------------------------------------------
SearchGraphplanAdapt::SearchGraphplanAdapt(const MapaObj& map) : BaseSearch{map}
{
    setSearchType("Graphplan");
}
//--------------------------------------------------------------------------------------------------
void SearchGraphplanAdapt::initLoopConditions()
{
    const std::set<uint16_t> firstLayer{_actualPath.begin()->getPointHash()};
    _newStatesPerIter.emplace_back(firstLayer);
}
//--------------------------------------------------------------------------------------------------
bool SearchGraphplanAdapt::extraCoonditionLoopSearch() const
{
    return (_newStatesPerIter.size() <= _limitSearchLayer);
}
//--------------------------------------------------------------------------------------------------
void SearchGraphplanAdapt::principalLoopSearch()
{
    const auto& layerStateSearch{_newStatesPerIter.rbegin()};

    if(!layerStateSearch->empty())
    {
        if(layerStateSearch->find(_endHash) != layerStateSearch->end())
        {
            // Let only destination state at last states
            _newStatesPerIter.rbegin()->clear();
            _newStatesPerIter.rbegin()->emplace(_endHash);

            // Backtrack and end search
            backTrackPath();

            // Find a route to say on best route, for now getting first route on backtrack
            backtrackFirstRoute();

            qDebug() << "End search finding an end";
            _keepSearchGoing = false;
        }
        else
        {
            // Does not have found end yet, will try to expand

            decltype(_allVisitedPoints) newStatesEncontered{};
            for(const uint16_t singleState : *layerStateSearch)
            {
                PointConnIter pointInfoIter{singleState, _connMapList->getConnectedMapElem(singleState)};
                while(!pointInfoIter.isAtEnd())
                {
                    newStatesEncontered.insert(pointInfoIter.getActualConnHash());
                    _searchStats.addNewPointVisited(pointInfoIter.getActualConnHash());

                    if(pointInfoIter.isOnLastValidIter())
                    {
                        break;
                    }
                    else
                    {
                        pointInfoIter.moveNext();
                    }
                }
            }

            decltype(_allVisitedPoints) intersectionStates{};

            std::set_intersection(newStatesEncontered.begin(), newStatesEncontered.end(),
                                  _allVisitedPoints.begin(), _allVisitedPoints.end(),
                                  std::inserter(intersectionStates, intersectionStates.begin()));

            for(const auto& intersectedItem : intersectionStates)
            {
                newStatesEncontered.extract(intersectedItem);
            }

            _newStatesPerIter.push_back(newStatesEncontered);
            _allVisitedPoints.merge(newStatesEncontered);
        }
    }
    else
    {
        qDebug() << "Fail search on Graphplan";
        _keepSearchGoing = false;
    }
}
//--------------------------------------------------------------------------------------------------
void SearchGraphplanAdapt::backTrackPath()
{
    for(auto iterStates = _newStatesPerIter.rbegin() ; _newStatesPerIter.rend() != iterStates ; iterStates++)
    {
        const auto iterStatesBefore{std::next(iterStates)};
        if(iterStatesBefore == _newStatesPerIter.rend())
        {
            break;
        }

        decltype(_allVisitedPoints) removeStatesAfter{};

        const auto& searchPoints{*iterStates};

        for(const uint16_t singleState : *iterStatesBefore)
        {
            PointConnIter pointInfoIter{singleState, _connMapList->getConnectedMapElem(singleState)};
            while(!pointInfoIter.isAtEnd())
            {
                if(searchPoints.find(pointInfoIter.getActualConnHash()) != searchPoints.end())
                {
                    removeStatesAfter.insert(pointInfoIter.getActualConnHash());
                    break;
                }

                if(pointInfoIter.isOnLastValidIter())
                {
                    break;
                }
                else
                {
                    pointInfoIter.moveNext();
                }
            }
        }

        for(const auto stateToRemove : removeStatesAfter)
        {
            iterStatesBefore->erase(stateToRemove);
        }
    }


}
//--------------------------------------------------------------------------------------------------
void SearchGraphplanAdapt::backtrackFirstRoute()
{
    _bestPath.emplace_front(_endHash, _connMapList->getConnectedMapElem(_endHash));
    decltype(_bestPathCost) bestCostSum{0};

    for(auto iterStates = _newStatesPerIter.rbegin() ; _newStatesPerIter.rend() != iterStates ; iterStates++)
    {
        const auto iterStatesBefore{std::next(iterStates)};
        if(iterStatesBefore == _newStatesPerIter.rend())
        {
            break;
        }

        const auto searchPoint{*(iterStates->begin())};

        bool endLoopEarly{false};
        for(const uint16_t singleState : *iterStatesBefore)
        {
            PointConnIter pointInfoIter{singleState, _connMapList->getConnectedMapElem(singleState)};
            while(!pointInfoIter.isAtEnd())
            {
                if(searchPoint == pointInfoIter.getActualConnHash())
                {
                    const auto addHash{pointInfoIter.getPointHash()};
                    PointConnIter pointConnInfoToAdd{addHash, _connMapList->getConnectedMapElem(addHash)};

                    Q_ASSERT(pointConnInfoToAdd.moveUntilFind(searchPoint));
                    bestCostSum += pointConnInfoToAdd.getActualConnCost();

                    _bestPath.emplace_front(pointConnInfoToAdd);
                    endLoopEarly = true;
                    break;
                }

                if(pointInfoIter.isOnLastValidIter())
                {
                    break;
                }
                else
                {
                    pointInfoIter.moveNext();
                }
            }

            if(endLoopEarly)
            {
                break;
            }

        }
        Q_ASSERT(endLoopEarly);
    }

    _bestPathCost = bestCostSum;
}
//--------------------------------------------------------------------------------------------------





























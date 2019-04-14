#include "searchlevel.h"
#include <limits>
#include <set>

#include <QDebug>
#include "pointobj.h"
#include "mapaobj.h"

SearchLevel::SearchLevel(const MapaObj& map, const std::string& startPoint, const std::string& endPoint) :
    baseSearch(map, startPoint, endPoint)
{

}

void SearchLevel::initLoopConditions()
{
    _startingPath = _actualPath;

    _actuallvlSearch = 1;
}

bool SearchLevel::extraCoonditionLoopSearch() const
{
    return (_maxlvlSearch > _actuallvlSearch);
}

void SearchLevel::principalLoopSearch()
{
    _keepSearchGoing = false;

    _actuallvlSearch++;
    while(_startingPath.size() < _actuallvlSearch)
    {
        const auto newConnHash{_startingPath.rbegin()->getActualConnHash()};
        _startingPath.emplace_back(newConnHash, _connMapList->getConnectedMapElem(newConnHash));
    }

    _actualPath = _startingPath;

    while(true)
    {
        auto actualElemIter{_actualPath.rbegin()};
        if(actualElemIter->getPointHash() != _endHash)
        {
            _keepSearchGoing |= validRoute();

        }
        else
        {
            calculateActualCost();

            // If solution is better
            if(_actualPathCost < _bestPathCost)
            {
                _bestPathCost = _actualPathCost;
                _bestPath = _actualPath;

                // If found best path, search still has meaning
                _keepSearchGoing = true;
            }
        }

        actualElemIter++;
        _actualPath.pop_back();
        if(actualElemIter->moveNext())
        {
            const auto newConnHash{actualElemIter->getActualConnHash()};
            _actualPath.emplace_back(newConnHash, _connMapList->getConnectedMapElem(newConnHash));
        }
        else
        {
            auto iterRedo{_actualPath.begin()};

            for(auto iterCheck = _actualPath.begin() ;
                _actualPath.end() != iterCheck ; iterCheck++)
            {
                if(iterCheck->isOnLastValidIter())
                {
                    iterRedo = iterCheck;
                    break;
                }
            }

            if(_actualPath.begin() != iterRedo)
            {
                auto iterBeforeRedo{std::prev(iterRedo)};

                // Should always be valid
                Q_ASSERT(iterBeforeRedo->moveNext());
                _actualPath.erase(std::next(iterBeforeRedo), _actualPath.end());
            }
            else
            {
                // Finish this lvl
                break;
            }

            // REDO route to lvl search
            while(_actualPath.size() < _actuallvlSearch)
            {
                const auto newConnHash{_actualPath.rbegin()->getActualConnHash()};
                _actualPath.emplace_back(newConnHash, _connMapList->getConnectedMapElem(newConnHash));
            }
        }
    }
}

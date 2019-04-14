#include "searchlevel.h"
#include <set>

#include "pointobj.h"

#include <QDebug>
//--------------------------------------------------------------------------------------------------
SearchLevel::SearchLevel(const MapaObj& map, const std::string& startPoint, const std::string& endPoint) :
    baseSearch(map, startPoint, endPoint)
{

}
//--------------------------------------------------------------------------------------------------
void SearchLevel::initLoopConditions()
{
    _startingPath = _actualPath;

    _actuallvlSearch = 1;
}
//--------------------------------------------------------------------------------------------------
bool SearchLevel::extraCoonditionLoopSearch() const
{
    return (_maxlvlSearch > _actuallvlSearch);
}
//--------------------------------------------------------------------------------------------------
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

        // Check if is solution
        const auto [isEnd, isLessExpensive] = validateEnd(actualElemIter->getPointHash());
        if(!isEnd)
        {
            _keepSearchGoing |= (isLessExpensive && validRoute());

            // Way slower than new implementation
            //_keepSearchGoing |= validRoute();
        }
        else
        {
            // If solution is better
            if(isLessExpensive)
            {
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
//--------------------------------------------------------------------------------------------------

#include "searchlevel.h"
#include <limits>
#include <set>

#include <QDebug>
#include "pointobj.h"
static MapaObj const* bla{nullptr};

SearchLevel::SearchLevel(const MapaObj& map, const std::string startPoint, const std::string endPoint) :
    _bestPathCost{std::numeric_limits<uint64_t>::max()}
{
    bla = &map;

    const auto startElem{map.getPointByName(startPoint)};
    if(startElem != nullptr)
    {
        _startHash = startElem->getHash();
    }

    const auto endElem{map.getPointByName(endPoint)};
    if(endElem != nullptr)
    {
        _endHash = endElem->getHash();
    }

    _connMapList = &map.getConnList();
}


bool SearchLevel::init()
{
    bool ret{false};

    _actualPath.emplace_back(_startHash, _connMapList->getConnectedMapElem(_startHash));

    auto startingPath{_actualPath};

    qDebug() << "First Conn hash" << _actualPath.begin()->getActualConnHash();

    bool keepSearchGoing{_startHash != _endHash};
    if(!keepSearchGoing)
    {
        _bestPath = _actualPath;
        _bestPathCost = 0;
    }

    uint64_t lvlSearch{1};

    const uint64_t maxlvlSearch{500};

    while(keepSearchGoing && (maxlvlSearch > lvlSearch))
    {
        keepSearchGoing = false;

        lvlSearch++;
        while(startingPath.size() < lvlSearch)
        {
            const auto newConnHash{startingPath.rbegin()->getActualConnHash()};
            startingPath.emplace_back(newConnHash, _connMapList->getConnectedMapElem(newConnHash));
        }

        _actualPath = startingPath;

        while(true)
        {
            auto actualElemIter{_actualPath.rbegin()};
            if(actualElemIter->getPointHash() != _endHash)
            {
                keepSearchGoing |= validRoute();

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
                    keepSearchGoing = true;
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
                while(_actualPath.size() < lvlSearch)
                {
                    const auto newConnHash{_actualPath.rbegin()->getActualConnHash()};
                    _actualPath.emplace_back(newConnHash, _connMapList->getConnectedMapElem(newConnHash));
                }
            }
        }
    }

    ret = !_bestPath.empty();

    qDebug() << "Final route if any\n";
    for(const auto& elemIt : _bestPath)
    {
        qDebug() << "Point " << QString::fromStdString(bla->getPoint(elemIt.getPointHash())->getName()) << " " << "Hash " << elemIt.getPointHash() << "Cost " << elemIt.getActualConnCost();
    }
    qDebug() << "\n Cost " << _bestPathCost;


    return ret;
}

void SearchLevel::calculateActualCost()
{
    _actualPathCost = 0;

//    qDebug() << "List size " << _actualPath.size();
    for(auto it{_actualPath.begin()} ; _actualPath.end() != it ; it++)
    {
        const auto itNext{std::next(it)};
        if(itNext == _actualPath.end())
        {
            break;
        }

        _actualPathCost += it->getActualConnCost();
//        qDebug() << "new cost "<< _actualPathCost;
    }
}

bool SearchLevel::validRoute() const
{
    std::set<uint16_t> nonRepPath{};

    std::vector<uint16_t> hashesPath{};
    hashesPath.reserve(_actualPath.size());

    for(const auto& elem : _actualPath)
    {
        const auto elemHash{elem.getPointHash()};
        hashesPath.push_back(elemHash);
        nonRepPath.insert(elemHash);
    }

    return nonRepPath.size() == hashesPath.size();
}

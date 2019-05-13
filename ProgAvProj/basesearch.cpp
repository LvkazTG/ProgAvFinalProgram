#include "basesearch.h"
#include <limits>
#include <set>

#include "pointobj.h"
#include "mapaobj.h"

#include <QDebug>

static MapaObj const* bla{nullptr};
//--------------------------------------------------------------------------------------------------
BaseSearch::BaseSearch(const MapaObj& map) : _bestPathCost{std::numeric_limits<uint64_t>::max()}
{
    bla = &map;

    _connMapList = &map.getConnList();
}
//--------------------------------------------------------------------------------------------------
void BaseSearch::definePoints(const uint16_t startP, const uint16_t endP)
{
    _startHash = startP;
    _endHash = endP;
}
//--------------------------------------------------------------------------------------------------
bool BaseSearch::init()
{
    bool ret{false};

    _searchStats.clear();

    _searchStats.startSearchtime();

    _actualPath.emplace_back(_startHash, _connMapList->getConnectedMapElem(_startHash));
    qDebug() << "First Conn hash" << _actualPath.begin()->getActualConnHash();

    _keepSearchGoing = _startHash != _endHash;
    if(!_keepSearchGoing)
    {
        _bestPath = _actualPath;
        _bestPathCost = 0;
    }
    else
    {
        initLoopConditions();
    }

//    initLoopConditions();

    // First check for starting point
    _searchStats.addNewPointVisited(_startHash);
    _searchStats.addIter();

    while(_keepSearchGoing && (_searchStats.getNumIters() < _maxNumIters) && extraCoonditionLoopSearch())
    {
        _searchStats.addIter();
        principalLoopSearch();
    }

    ret = !_bestPath.empty();

    qDebug() << "Final route if any\n";
    for(const auto& elemIt : _bestPath)
    {
        qDebug() << "Point " << QString::fromStdString(bla->getPoint(elemIt.getPointHash())->getName()) << " " << "Hash " << elemIt.getPointHash() << "Cost " << elemIt.getActualConnCost();
    }
    qDebug() << "\n Cost " << _bestPathCost;

    _searchStats.endSearchTime();

    return ret;
}
//--------------------------------------------------------------------------------------------------
void BaseSearch::calculateActualCost()
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
//--------------------------------------------------------------------------------------------------
bool BaseSearch::validRoute() const
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
//--------------------------------------------------------------------------------------------------
std::tuple<const bool, const bool> BaseSearch::validateEnd(const uint16_t pointHash)
{
    calculateActualCost();

    const std::tuple<const bool, const bool> ret{{pointHash == _endHash},
                                                 {_actualPathCost < _bestPathCost}};

    if(std::get<0>(ret))
    {
        _searchStats.addNewPathCost(_actualPathCost);

        if(std::get<1>(ret))
        {
            _bestPathCost = _actualPathCost;
            _bestPath = _actualPath;
        }
    }

    return ret;
}
//--------------------------------------------------------------------------------------------------
const SearchStatistics& BaseSearch::getSearchStatistics() const
{
    return _searchStats;
}
//--------------------------------------------------------------------------------------------------
const std::string& BaseSearch::getSearchType()
{
    return _searchStats.getSearchMethodName();
}
//--------------------------------------------------------------------------------------------------
const std::list<PointConnIter>& BaseSearch::getBestPath() const
{
    return _bestPath;
}
//--------------------------------------------------------------------------------------------------
uint64_t BaseSearch::getBestPathCost() const
{
    return _bestPathCost;
}
//--------------------------------------------------------------------------------------------------
void BaseSearch::setSearchType(const std::string& type)
{
    _searchStats.setSearchMethodName(type);
}
//--------------------------------------------------------------------------------------------------

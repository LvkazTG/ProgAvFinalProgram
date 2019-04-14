#include "basesearch.h"
#include <limits>
#include <set>

#include "pointobj.h"
#include "mapaobj.h"

#include <QDebug>

static MapaObj const* bla{nullptr};
//--------------------------------------------------------------------------------------------------
baseSearch::baseSearch(const MapaObj& map, const std::string& startPoint, const std::string& endPoint) :
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
//--------------------------------------------------------------------------------------------------
bool baseSearch::init()
{
    bool ret{false};

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

    while(_keepSearchGoing && extraCoonditionLoopSearch())
    {
        principalLoopSearch();
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
//--------------------------------------------------------------------------------------------------
void baseSearch::calculateActualCost()
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
bool baseSearch::validRoute() const
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
std::tuple<const bool, const bool> baseSearch::validateEnd(const uint16_t pointHash)
{
    calculateActualCost();

    const std::tuple<const bool, const bool> ret{{pointHash == _endHash},
                                                 {_actualPathCost < _bestPathCost}};

    if(std::get<0>(ret) && std::get<1>(ret))
    {
        _bestPathCost = _actualPathCost;
        _bestPath = _actualPath;
    }

    return ret;
}
//--------------------------------------------------------------------------------------------------

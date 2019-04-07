#include "connlist.h"
//--------------------------------------------------------------------------------------------------
ConnList::ConnList()
{
}
//--------------------------------------------------------------------------------------------------
void ConnList::connectPoints(std::shared_ptr<PointObj> point, const std::map<uint16_t, uint8_t>& newConns)
{
    connectPoints(point->getHash(), newConns);
}
//--------------------------------------------------------------------------------------------------
void ConnList::connectPoints(const uint16_t pointHash, const std::map<uint16_t, uint8_t>& newConns)
{
    _connectedPoints.emplace(std::make_pair(pointHash, newConns));
}
//--------------------------------------------------------------------------------------------------
void ConnList::connectPoints(std::shared_ptr<PointObj> point, const std::vector<std::tuple<uint8_t, uint16_t>>& newConns)
{
    std::map<uint16_t, uint8_t> provMap{};
    for(const auto& newElem : newConns)
    {
        provMap.emplace(std::get<1>(newElem), std::get<0>(newElem));
    }

    _connectedPoints.emplace(point->getHash(), std::move(provMap));
}
//--------------------------------------------------------------------------------------------------
void ConnList::connectNewPoint(std::shared_ptr<PointObj> point, std::shared_ptr<PointObj> newPoint, const uint8_t connCost)
{
    connectNewPoint(point->getHash(), newPoint, connCost);
}
//--------------------------------------------------------------------------------------------------
void ConnList::connectNewPoint(const uint16_t pointHash, std::shared_ptr<PointObj> newPoint, const uint8_t connCost)
{
    const auto newPointHash{newPoint->getHash()};
    connectNewPoint(pointHash, newPointHash, connCost);
}
//--------------------------------------------------------------------------------------------------
void ConnList::connectNewPoint(const uint16_t pointHash, const uint16_t newPointHash, const uint8_t connCost)
{
    _connectedPoints[pointHash].emplace(std::make_pair(newPointHash, connCost));
}
//--------------------------------------------------------------------------------------------------
const std::map<uint16_t, std::map<uint16_t, uint8_t>>& ConnList::getConnectedMap() const
{
    return _connectedPoints;
}
//--------------------------------------------------------------------------------------------------
const std::map<uint16_t, uint8_t>& ConnList::getConnectedMapElem(std::shared_ptr<PointObj> point) const
{
    return getConnectedMapElem(point->getHash());
}
//--------------------------------------------------------------------------------------------------
const std::map<uint16_t, uint8_t>& ConnList::getConnectedMapElem(const uint16_t elemHash) const
{
    //To do, ADD a try catch statement for invalid searches
    return _connectedPoints.at(elemHash);
}
//--------------------------------------------------------------------------------------------------
void ConnList::createEmptyHashEntry(const uint16_t elemHash)
{
    _connectedPoints[elemHash] = {};
}

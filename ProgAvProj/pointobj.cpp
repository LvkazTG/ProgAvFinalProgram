#include "pointobj.h"
#include <math.h>

PointObj::PointObj(const uint8_t newX, const uint8_t newY) : _xCoord{newX}, _yCoord{newY}
{
    _pHash = (static_cast<uint16_t>(_xCoord << 8)) | _yCoord;
}

double PointObj::distFrom(PointObj otherPoint) const
{
    return sqrt(pow(this->_xCoord-otherPoint.getX(),2) + pow(this->_yCoord-otherPoint.getY(),2));
}

uint8_t PointObj::getX() const
{
    return _xCoord;
}

uint8_t PointObj::getY() const
{
    return _yCoord;
}

uint16_t PointObj::getHash() const
{
    return _pHash;
}

void PointObj::connectPoints(const std::map<uint16_t, uint8_t>& newConns)
{
    _connectedPoints = newConns;
}

void PointObj::connectPoints(const std::vector<std::tuple<uint8_t, uint16_t> > &newConns)
{
    for(const auto& newElem : newConns)
    {
        _connectedPoints.emplace(std::get<1>(newElem), std::get<0>(newElem));
    }
}

void PointObj::connectNewPoint(std::shared_ptr<PointObj> newPoint, const uint8_t connCost)
{
    const auto newPointHash{newPoint->getHash()};
    _connectedPoints.emplace(newPointHash, connCost);
}

const std::map<uint16_t, uint8_t> &PointObj::getConnectedMap() const
{
    return _connectedPoints;
}

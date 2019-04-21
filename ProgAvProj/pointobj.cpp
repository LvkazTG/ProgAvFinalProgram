#include "pointobj.h"
#include <math.h>

PointObj::PointObj(const uint8_t newX, const uint8_t newY) : _xCoord{newX}, _yCoord{newY}
{
    _pHash = calcHash(_xCoord, _yCoord);

    //Debug
    createFakeName();
}

double PointObj::distFrom(const PointObj& otherPoint) const
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

const std::string& PointObj::getName()
{
    return _pName;
}

void PointObj::setName(const std::string& newName)
{
    _pName = newName;
}

void PointObj::createFakeName()
{
    _pName = "point_" + std::to_string(_xCoord) + "_" + std::to_string(_yCoord);
}

uint16_t PointObj::calcHash(const uint8_t xCoord, const uint8_t yCoord)
{
    return ((static_cast<uint16_t>(xCoord << 8)) | yCoord);
}

#ifndef POINTOBJ_H
#define POINTOBJ_H

#include <stdint.h>
#include <string>
#include <memory>
#include <vector>
#include <map>


class PointObj
{
public:
    PointObj(const uint8_t x, const uint8_t y);

    uint8_t getX() const;
    uint8_t getY() const;
    uint16_t getHash() const;

    const std::string& getName();
    void setName(const std::string& newName);


    double distFrom(const PointObj& otherPoint) const;

//    void connectPoints(const std::map<uint16_t, uint8_t>& newConns);
//    void connectPoints(const std::vector<std::tuple<uint8_t, uint16_t>>& newConns);

//    void connectNewPoint(std::shared_ptr<PointObj> newPoint, const uint8_t connCost);

//    const std::map<uint16_t, uint8_t>& getConnectedMap() const;

private:
    std::string _pName{""};
    const uint8_t _xCoord{0};
    const uint8_t _yCoord{0};
    uint16_t _pHash{0};


    void createFakeName();

};

#endif // POINTOBJ_H

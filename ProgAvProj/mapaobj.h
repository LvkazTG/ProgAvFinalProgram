#ifndef MAPAOBJ_H
#define MAPAOBJ_H

#include "pointobj.h"
#include <vector>
#include <map>
#include <memory>
#include <connlist.h>

class MapaObj
{
public:
    MapaObj();
    MapaObj(const uint8_t xSize, const uint8_t ySize);

    void criaMapa();

    void PrintConnectEdelems() const;

    void createNew();

    uint8_t getXSize() const;
    uint8_t getYSize() const;

    void setName(const std::string& newName);
    const std::string& getName() const;

    const ConnList& getConnList() const;

    const std::shared_ptr<PointObj>& getPoint(const uint16_t pointHash) const;
    const std::shared_ptr<PointObj>& getPointByCoord(const uint8_t xCoord, const uint8_t yCoord) const;
    const std::shared_ptr<PointObj> getPointByName(const std::string& pointName) const;


    void initMap(const std::vector<std::shared_ptr<PointObj>>& points, const ConnList& connList);

    const std::map<uint16_t, std::shared_ptr<PointObj>>& getAllPoints() const;

private:
    void createConnectionsMatrix();

    void initMap(std::map<uint16_t, std::shared_ptr<PointObj>> points, ConnList connList);

    const uint8_t _xSize{5};
    const uint8_t _ySize{5};
    ConnList _connectedList{};
    const uint8_t _maxConnectionsPerPoint{5};
    const uint8_t _maxConnectionDist{4};
    bool finishedMapa{false};
    std::string _mapName{};
    std::map<uint16_t, std::shared_ptr<PointObj>> _points{};
};

#endif // MAPAOBJ_H

#ifndef MAPAOBJ_H
#define MAPAOBJ_H

#include "pointobj.h"
#include <vector>
#include <map>
#include <memory>
#include <connlist.h>

//class ConnList;

class MapaObj
{
public:
    MapaObj();
    MapaObj(const uint8_t xSize, const uint8_t ySize);

    void criaMapa();


    void PrintConnectEdelems() const;

    const uint8_t _xSize{5};
    const uint8_t _ySize{5};

    void createNew();

    uint8_t getXSize() const;
    uint8_t getYSize() const;

//    std::vector<PointObj> _points{};
    void setName(const std::string& newName);
    const std::string& getName() const;

    const ConnList& getConnList() const;
    const std::shared_ptr<PointObj>& getPoint(const uint16_t pointHash) const;

    void initMap(const std::vector<std::shared_ptr<PointObj>>& points, const ConnList& connList);

    std::map<uint16_t, std::shared_ptr<PointObj>> _points{};

private:
    void createConnectionsMatrix();

    void initMap(std::map<uint16_t, std::shared_ptr<PointObj>> points, ConnList connList);

    ConnList _connectedList{};
    uint8_t _maxConnectionsPerPoint{4};
    bool finishedMapa{false};
    std::string _mapName{};

};

#endif // MAPAOBJ_H

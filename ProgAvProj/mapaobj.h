#ifndef MAPAOBJ_H
#define MAPAOBJ_H

#include "pointobj.h"
#include <vector>
#include <map>
#include <memory>

class MapaObj
{
public:
    MapaObj();
    MapaObj(const uint8_t xSize, const uint8_t ySize);

    void criaMapa();


    void PrintConnectEdelems();

    const int _xSize{5};
    const int _ySize{5};

//    std::vector<PointObj> _points{};

    std::map<uint16_t, std::shared_ptr<PointObj>> _points{};

private:
    void init();
    void createConnectionsMatrix();

    uint8_t _maxConnectionsPerPoint{4};
    bool finishedMapa{false};

};

#endif // MAPAOBJ_H

#include "mapaobj.h"

#include <algorithm>
#include <random>

#include <QDebug>
//--------------------------------------------------------------------------------------------------
MapaObj::MapaObj()
{
    init();
}
//--------------------------------------------------------------------------------------------------
MapaObj::MapaObj(const uint8_t xSize, const uint8_t ySize) : _xSize{xSize}, _ySize{ySize}
{
    init();
}
//--------------------------------------------------------------------------------------------------
void MapaObj::init()
{
//    _points.reserve(_xSize*_ySize);

    for(uint8_t x_index = 0 ; x_index < _xSize; x_index++)
    {
        for(uint8_t y_index = 0 ; y_index < _ySize; y_index++)
        {
            auto newPoint{std::make_shared<PointObj>(x_index, y_index)};
            const auto pointHash{newPoint->getHash()};
            _points.emplace(pointHash, std::move(newPoint));
//            _points.emplace_back(x_index, y_index);
        }
    }

    createConnectionsMatrix();
}
//--------------------------------------------------------------------------------------------------
void MapaObj::createConnectionsMatrix()
{
    auto rng = std::default_random_engine {};

    const uint8_t distorceDistVal{4};
    const uint8_t maxConnectionDist{25};

    std::vector<std::vector<std::tuple<uint8_t, uint16_t>>> matrixValues{};

    for(const auto& elem1 : _points)
    {
        matrixValues.emplace_back();
        auto newLastIndexMatrix{matrixValues.rbegin()};
        for(const auto& elem2 : _points)
        {
//            const auto pDist{static_cast<uint32_t>(elem1.distFrom(elem2))};
            const auto pDist{static_cast<uint32_t>(elem1.second->distFrom(*(elem2.second)))};
            if(pDist < maxConnectionDist)
            {
                const auto connectedPoint{(rand() % 2)};
                if(connectedPoint != 0)
                {
                    const uint32_t connectionCost{(pDist*(rand()% distorceDistVal)/distorceDistVal)};
                    if(connectionCost != 0)
                    {
                        newLastIndexMatrix->emplace_back(connectionCost, elem2.second->getHash());
                    }
//                    newLastIndexMatrix->emplace_back(connectionCost, elem2.getHash());
                }
            }
        }

        std::shuffle(std::begin(*newLastIndexMatrix), std::end(*newLastIndexMatrix), rng);

        if(newLastIndexMatrix->size() > _maxConnectionsPerPoint)
        {
            newLastIndexMatrix->resize(_maxConnectionsPerPoint);
        }

        elem1.second->connectPoints(*newLastIndexMatrix);
    }
}
//--------------------------------------------------------------------------------------------------
void MapaObj::PrintConnectEdelems()
{
    for(const auto& elem : _points)
    {
        qDebug() << "Elem hash" << elem.first << " confirmed " << elem.second->getHash();
        const auto elemConnInfo{elem.second->getConnectedMap()};

        auto printItem{qDebug()};
        printItem << "Connected to hashes";
        for(const auto& connPoint : elemConnInfo)
        {
            printItem << connPoint.first << " cost " << connPoint.second << "//";
        }
    }

    qDebug() << "Num points" << _points.size();
}
//--------------------------------------------------------------------------------------------------


















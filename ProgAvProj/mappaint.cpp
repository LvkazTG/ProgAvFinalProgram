#include "mappaint.h"

#include "mapaobj.h"

#include <QPainter>

MapPaint::MapPaint(QWidget *parent) : QWidget{parent}
{
}

void MapPaint::addMap(const MapaObj* map)
{
    _map = map;
    update();
}

void MapPaint::paintEvent(QPaintEvent *)
{
    if(nullptr != _map)
    {
        const uint32_t separatorMultiplier{50};

        QPainter paintTool{this};

        // Draw Points
        for(const auto& singlePointData : _map->getAllPoints())
        {
            const auto& singlePoint{singlePointData.second};
            paintTool.drawPoint(singlePoint->getX()*separatorMultiplier,
                                singlePoint->getY()*separatorMultiplier);
        }

        // Draw connection lines
        for(const auto& singlePointConnData : _map->getConnList().getConnectedMap())
        {
            const auto& firstPoint{_map->getPoint(singlePointConnData.first)};
            for(const auto& connectedData : singlePointConnData.second)
            {
                const auto& secondPoint{_map->getPoint(connectedData.first)};
                paintTool.drawLine(firstPoint->getX()*separatorMultiplier,
                                   firstPoint->getY()*separatorMultiplier,
                                   secondPoint->getX()*separatorMultiplier,
                                   secondPoint->getY()*separatorMultiplier);
            }
        }

        this->setMinimumSize(((_map->getXSize()*separatorMultiplier)+10), ((_map->getYSize()*separatorMultiplier)+10));
    }
}


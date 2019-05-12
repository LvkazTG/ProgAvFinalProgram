#include "routeresultpaint.h"
#include <QPainter>

#include "pointconniter.h"
#include "mapaobj.h"
//--------------------------------------------------------------------------------------------------
RouteResultPaint::RouteResultPaint(QWidget *parent) : QWidget(parent)
{

}
//--------------------------------------------------------------------------------------------------
void RouteResultPaint::addRouteAndMap(const std::list<PointConnIter>* routeList,
                                      const MapaObj* map)
{
    _listRoute = routeList;
    _map = map;
    update();
}
//--------------------------------------------------------------------------------------------------
void RouteResultPaint::paintEvent(QPaintEvent *)
{
    if((nullptr != _listRoute) && (nullptr != _map))
    {
        if(!_listRoute->empty())
        {
            const uint32_t separatorMultiplier{50};
            const uint32_t lateralOffset{5};

            QPainter paintTool{this};
            QPen pen{Qt::black};
            pen.setWidth(2);
            paintTool.setPen(pen);

            // Draw connection lines
            // Last Point wont be connected
            for(auto singleElem{(*_listRoute).begin()} ;
                std::prev((*_listRoute).end()) !=  singleElem ; singleElem++)
            {

                const auto& firstPoint{_map->getPoint(singleElem->getPointHash())};
                const auto& secondPoint{_map->getPoint(singleElem->getActualConnHash())};

                paintTool.drawLine(firstPoint->getX()*separatorMultiplier+lateralOffset,
                                   firstPoint->getY()*separatorMultiplier+lateralOffset,
                                   secondPoint->getX()*separatorMultiplier+lateralOffset,
                                   secondPoint->getY()*separatorMultiplier+lateralOffset);
            }


            // Points after so lines wont repaint them
            pen.setColor(Qt::blue);
            pen.setWidth(5);
            paintTool.setPen(pen);

            // Change color for points

            // Draw Points
            for(const auto& singleElem : *_listRoute)
            {
                const auto& pointObj{_map->getPoint(singleElem.getPointHash())};
                paintTool.drawPoint(pointObj->getX()*separatorMultiplier+lateralOffset,
                                    pointObj->getY()*separatorMultiplier+lateralOffset);
            }

            // Change point begin and end color
            pen.setColor(Qt::red);
            pen.setWidth(10);
            paintTool.setPen(pen);

            const auto& pointObjStart{_map->getPoint((*_listRoute).begin()->getPointHash())};
            paintTool.drawPoint(pointObjStart->getX()*separatorMultiplier+lateralOffset,
                                pointObjStart->getY()*separatorMultiplier+lateralOffset);

            pen.setColor(Qt::green);
            pen.setWidth(7);
            paintTool.setPen(pen);

            const auto& pointObjEnd{_map->getPoint((*_listRoute).rbegin()->getPointHash())};
            paintTool.drawPoint(pointObjEnd->getX()*separatorMultiplier+lateralOffset,
                                pointObjEnd->getY()*separatorMultiplier+lateralOffset);


            this->setMinimumSize(((_map->getXSize()*separatorMultiplier)+10+lateralOffset),
                                 ((_map->getYSize()*separatorMultiplier)+10+lateralOffset));

        }
        else
        {
            // Should log something
        }
    }
}
//--------------------------------------------------------------------------------------------------
